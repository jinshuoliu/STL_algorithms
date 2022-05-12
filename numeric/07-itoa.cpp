template <class ForwardIterator, class T>
void itoa(ForwardIterator first, ForwardIterator last, T value) {
  while (first != last)
    *first++ = value++; // 直接改变区间内的值
}