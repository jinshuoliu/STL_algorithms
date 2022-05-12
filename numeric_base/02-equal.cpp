template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first, InputIterator1 lase1, InputIterator2 first2) {
  // 它是看对位元素相等就可以
  // 它还是少考虑一些问题
  // 如果区间2的元素比区间1多呢？
  // 如果区间2的元素少，它继续++那元素是其他区域的，会导致一些不可预知的错误吗？
  for(;first1 != last1; ++first1, ++first2)
    if(*first1 != *first2)
      return false;
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first, InputIterator1 lase1, InputIterator2 first2, BinaryPredicate binary_pred) {
  for(;first1 != last1; ++first1, ++first2)
    if(!binary_pred(*first1, *first2))
      return false;
  return true;
}