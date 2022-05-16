template <class RandomAccessIterator>
inline void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last){
  __nth_element(first, nth, last, value_type(first));
}

// 辅助函数
template <class RandomAccessIterator, class T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, T*) {
  while(last-first>3){ // 长度超过3，函数才有意义
    // 采用median-of-3 partitioning
    // 分割
    RandomAccessIterator cut = __unguarded_partition(
      first, last, T(__median(
        *first, *(first+(last-first)/2), *(last-1)
      ))
    );
    if(cut<=nth)
      first = cut;
    else
      last = cut;
  }
  // 重排序
  __insertion_sort(first, last);
}