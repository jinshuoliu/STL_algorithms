// 版本1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
  while(first1!=last1 && first2!=last2) {
    if(*first1<*first2){
      *result = *first1;
      ++first1;
      ++result;
    }
    else if(*first2<*first1){
      *result = *first2;
      ++first2;
      ++result;
    }
    else{
      ++first1;
      ++first2;
    }
  }
  return copy(first2, last2, copy(first1, last1, result));
}

// 版本2，通过仿函数来比较大小
template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperator>
OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryOperator binary_op) {
  while(first1!=last1 && first2!=last2) {
    if(binary_op(*first1, *first2)){
      *result = *first1;
      ++first1;
      ++result;
    }
    else if(binary_op(*first2, *first1)){
      *result = *first2;
      ++first2;
      ++result;
    }
    else{
      ++first1;
      ++first2;
    }
  }
  return copy(first2, last2, copy(first1, last1, result));
}