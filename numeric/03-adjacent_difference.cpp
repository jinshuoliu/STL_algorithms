// 版本1
template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
  if(first == last)
    return result;
  *result = *first; // 第一个值可以直接赋给value的，因为它前面没有值
  return __adjacent_difference(first, last, result, value_type(first));
}

// 既然只有版本1调用它，为什么不把它直接实现在版本1中，而要在外面创建它呢？
template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*) {
  T value = *first;
  while(++first != last) {
    T tmp = *first; // tmp与value指向相同的指针，不过tmp比value快一步
    *++result = tmp - value; // 把 后-前 的值赋给后面那个元素
    value = tmp;
  }
  return ++result;
}

// 版本2
template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
  if(first == last)
    return result;
  *result = *first;
  return __adjacent_difference(first, last, result, value_type(first), binary_op);
}

template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperation binary_op) {
  T value = *first;
  while(++first != last) {
    T tmp = *first;
    *++result = binary_op(tmp - value);
    value = tmp;
  }
  return ++result;
}