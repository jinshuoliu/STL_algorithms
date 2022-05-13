// 版本1
template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op) {
  for(; first != last; ++first, ++result)
    *result = op(*first);
  return result;
}

// 版本2
template <class InputerIterator1, class InputerIterator2, class OutputIterator, class BinaryOperation>
OutputIterator transfrom(InputerIterator1 first1, InputerIterator1 last1, InputerIterator2 first2, OutputIterator result, BinaryOperation binary_op) {
  for(; first1 != last1; ++first1, ++first2, ++result)
    *result = binary_op(*first1, *first2);
  return result;
}