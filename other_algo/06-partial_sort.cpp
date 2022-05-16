// 版本1
template <class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
  __partial_sort(first, middle, last, value_type(first));
}

template <class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*) {
  // 把前半部分改为heap，便于查找最大值
  make_heap(first, middle);
  for(RandomAccessIterator i = middle; i<last; ++i)
    if(*i<*first)
      __pop_heap(first, middle, i, T(*i), distance_type(first));
  // 重新排列
  sort_heap(first, middle);
}

/* partial_sort_copy */
template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last);

template <class InputIterator, class RandomAccessIterator, class Compare>
inline RandomAccessIterator partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first, RandomAccessIterator result_last, Compare comp);