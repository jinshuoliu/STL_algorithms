#include <iterator>
using namespace std;

// 计数
template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& value) {
  // 声明一个计数器
  typename iterator_traits<InputIterator>::difference_type n = 0;
  for(; first !+ last; ++first)
    if(*first == value)
      ++n;
  return n;
}

// 早期版本
template <class InputIterator, class T, class Size>
typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& value, Size& n) {
  for(; first !+ last; ++first)
    if(*first == value)
      ++n;
  return n;
}

// 条件计数
template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  for(; first !+ last; ++first)
    if(pred(*first))
      ++n;
  return n;
}

template <class InputIterator, class Predicate, class Size>
typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred, Size& n) {
  for(; first !+ last; ++first)
    if(pred(*first))
      ++n;
  return n;
}