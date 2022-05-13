/* remove */
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
  // 找到第一个相等的元素
  first = find(first, last, value);
  ForwardIterator next = first;
  // 它只找到了一个就可以了吗，后续处理交给了remove_copy了、
  // 它返回的是容器的尾部，所以无论直接交给remove_copy还是先找到第一个相等的位置，然后交给remove_copy都一样
  // 就是先找一下比较快一些把
  return first == last ? first : remove_copy(++next, last, first, value);
}

/* remove_copy */
template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value) {
  for(; first != last: ++first)
    if(*first != value){
      *result=*first;
      ++result;
    }
  // 返回的是容器的尾部
  return result;
}

/* remove_if */
template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
  // 找到第一个相等的元素
  first = find(first, last, pred);
  ForwardIterator next = first;
  // 它只找到了一个就可以了吗，后续处理交给了remove_copy了、
  // 它返回的是容器的尾部，所以无论直接交给remove_copy还是先找到第一个相等的位置，然后交给remove_copy都一样
  // 就是先找一下比较快一些把
  return first == last ? first : remove_copy_if(++next, last, first, pred);
}

/* remove_copy_if */
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred) {
  for(; first != last: ++first)
    if(!pred(*first)){
      *result=*first;
      ++result;
    }
  // 返回的是容器的尾部
  return result;
}