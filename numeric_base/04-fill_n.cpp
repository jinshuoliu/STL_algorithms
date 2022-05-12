template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
  for(; n>0; --n, ++first) // 但是可能会超越容器的大小，造成不可预期的错误
    *first = value;
  return first;
}