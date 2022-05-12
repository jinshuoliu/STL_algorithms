// 版本1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
  while(first1!=last1 && first2!=last2) {
    // 这里体现出有序容器是该算法的基础
    if(*first1<*first2){
      *result = *first1;
      ++first1;
    }
    else if(*first2<*first1){
      *result = *first2;
      ++first2;
    }
    else{
      // 这里就体现出了：如果两个区间内分别存在m、n个，那么结果区间内它的数量是max(m, n)
      *result = *first1;
      ++first1;
      ++first2;
    }
    ++result;
  }
  // 不去判断谁空了，直接都拷贝进来，反正要是空了就拷贝个空
  return copy(first2,last2, copy(first1, last1, result));
}

// 版本2，通过仿函数来比较大小
template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, BinaryOperator binary_op) {
  while(first1!=last1 && first2!=last2) {
    if(binary_op(*first1, *first2)){
      *result = *first1;
      ++first1;
    }
    else if(binary_op(*first2, *first1)){
      *result = *first2;
      ++first2;
    }
    else{
      *result = *first1;
      ++first1;
      ++first2;
    }
    ++result;
  }
  return copy(first2,last2, copy(first1, last1, result));
}