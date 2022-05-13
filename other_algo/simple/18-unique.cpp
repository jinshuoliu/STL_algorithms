/* unique */
// 版本1
template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
  // 查找相邻元素位置
  first = adjacent_find(first, last);
  // 交给unique_copy来处理
  return unique_copy(first, last, first);
}

/* unique_copy */
// 版本1
template <class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result) {
  if(first == last)
    return result;
  return __unique_copy(first, last, result, iterator_category(result));
}

#include <iterator>
using namespace std;

// 辅助函数forward_iterator_tag版
template <class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag) {
  *result = *first;
  while(++first != last)
    if(*result != *first)
      *++result = *first;
  return ++result;
}

// 辅助函数output_iterator_tag版
template <class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag) {
  return __unique_copy(first, last, result, value_type(first));
}
// 由于output iterator是write only，无法读取，所以设计这一版本
template <class InputIterator, class OutputIterator, class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
  T value = *first;
  *result = value;
  while(++first != last)
    if(value != *first){
      value = *first;
      *++result = value;
    }
  return ++result;
}