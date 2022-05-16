/* Insertion Sort */
// 版本1
template <class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
  if(first == last)
    return;
  for(RandomAccessIterator i = first + 1; i != last; ++i)
    __linear_insert(first, i, value_type(first));
}

// 版本1辅助函数
template <class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*) {
  T value = *last;
  if(value < *first) {
    // 这样操作不会改变下一次循环将要传进来的空间的最后一个元素的值吗？
    // sort操作是质变操作的把
    copy_backward(first, last, last+1);
    *first = value;
  }
  else
    __unguarded_linear_insert(last, value); // 这里last指向的位置存的就是value，但是value是个值，而last是个位置，还是有很大不同的
}

// 版本1辅助函数，为value找一个正确的位置
template <class RandomAccessIterator, class T>
// 侯捷的注解：这里命名为unguarded是因为正常操作应该加上是否超过边界的判断，但是由于前面的for导致不用进行此判断
void __unguarded_linear_insert(RandomAccessIterator last, T value) {
  RandomAccessIterator next = last;
  --next;
  while(value<*next) {
    *last = *next;
    last = next;
    --next;
  }
  *last = value;
}

/* Quick Sort */
// 三点中值的决定函数
template <class T>
inline const T& __median(const T& a, const T& b, const T& c) {
  if(a<b)
    if(b<c)
      return b;
    else if(a<c)
      return c;
    else 
      return a;
  else if(a<c)
    return a;
  else if(b<c)
    return c;
  else
    return b;
}

// 分割函数
template <class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, T pivot){
  while(true){
    while(*first<pivot)
      ++first;
    --last;
    while(pivot<*last)
      --last;
    if(!(first<last))
      return first;
    iter_swap(first, last);
    ++first;
  }
}

/* SGI STl sort */
template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
  if(first != last) {
    // IntroSort，相对普通是Qick Sort中间有防止恶化的操作
    __introsort_loop(first, last, value_type(first), __lg(last-first)*2);
    // 进行最后的Insertion Sort操作
    __final_insertion_sort(first, last);
  }
}

// 用来控制分割恶化的情况
template <class Size>
inline Size __lg(Size n) {
  Size k;
  // 找出2^k <= n 的最大值k
  for(k=0; n>1; n>>=1)
    ++k;
  return k;
}

const int __stl_threshold = 16;

// Introsort
// 当元素个数为40时，__introsoft_loop()的最后一个参数是5*2，意为最多允许分割10层
template <class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*, Size depth_limit) {
  // __stl_threshold是全局常数，定义为 const int 16
  while(last-first > __stl_threshold){
    // intro sort防止恶化
    if(depth_limit==0){ // 分割恶化，改用heapsort
      partial_sort(first, last, last);
      return;
    }
    --depth_limit;
    // median-of-3 partition
    RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first+(last-first)/2), *(last-1))));
    // 对右半段递归进行sort
    __introsort_loop(cut, last, value_type(first), depth_limit);
    last = continue;
    // 进行while循环，对左半段递归进行sort
  }
}

// __introsort_loop函数结束的时候[first,last)内有多个元素个数少于16的子序列，他们都符合快排好了的情况
template <class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
  if(last-first > __stl_threshold){ // 通过元素个数来控制后续的操作
    // 将元素分为两部分：一部分有16个，另一部分是剩余的
    __insertion_sort(first, first+__stl_threshold);
    // 后面这些是要给他们直接排好顺序的
    __unguarded_insertion_sort(first + __stl_threshold, last);
  }
  else
    // 当元素只有少于或等于16的时候进行insertion sort操作
    __insertion_sort(first, last);
}

template <class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
  __unguarded_insertion_sort_aux(first, last, value_type(first));
}
template <class RandomAccessIterator, class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
  for(RandomAccessIterator i = first; i!=last; ++i)
    __unguarded_linear_insert(i, T(*i));
}


/* RW STL sort */
// 它用的是纯粹的Quick Sort，并没有使用IntroSort
template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
  if(!(first==last)){
    __quick_sort_loop(first, last);
    __final_insertion_sort(first, last);
  }
}
template <class RandomAccessIterator>
inline void __quick_sort_loop(RandomAccessIterator first, RandomAccessIterator last){
  __quick_sort_loop_aux(first, last, __RWSTD_VALUE_TYPE(first));
}
template <class RandomAccessIterator, class T>
void __quick_sort_loop_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
  while(last-first > __stl_threshold) {
    // median-of-3 partition
    RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first+(last-first)/2), *(last-1))));
    // 很明显的对两半部分进行递归操作
    if(cut-first >= last-cut) {
      __quick_sort_loop(cut, last);
      last = cut;
    }
    else {
      __quick_sort_loop(first, cut);
      first = cut;
    }
  }
}