// 版本1
template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
  if (first == last)
    return last;
  ForwardIterator next = first;
  while (++next != last) {
    if(*first == *next) // 找到相邻且相等
      return first;
    first = next;
  }
  return last;
}

// 版本2
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred) {
  if (first == last)
    return last;
  ForwardIterator next = first;
  while (++next != last) {
    if(binary_pred(*first, *next)) // 找到相邻且相等
      return first;
    first = next;
  }
  return last;
}