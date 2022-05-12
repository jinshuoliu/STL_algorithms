// 版本1
template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
  for(; first1 != last1; ++first1, ++first2) // 使用第一个区间的范围还能控制第二个区间的范围，所以第二区间必须大于等于第一区间的大小
    init = init + (*first1 * *first2);
  return init;
}

// 版本2
template <class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2) {
  for(; first1 != last1; ++first1, ++first2)
    init = binary_op1(init + binary_op2(*first1, *first2));
  return init;
}