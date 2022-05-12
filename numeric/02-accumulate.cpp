// 版本1
// 这是一个带初值的求和
template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
  for(;first != last; ++first)
    init = init + *first; // 将每个元素累加到初值init
  return init;
}

// 版本2
template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
  for(; first != last; ++first)
    init = binary_op(init, *first); // 每次都执行二元操作，具体是什么操作要看传进来的BinaryOperation
  return init;
}