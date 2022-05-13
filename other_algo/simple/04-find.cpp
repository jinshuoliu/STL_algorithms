/* 查找 */
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
  while(first != last && *first != value)
    ++first;
  return first;
}

/* 条件查找 */
template <class InputIterator, class T, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
  while(first != last && pred(*first))
    ++first;
  return first;
}

/* 查找一个空间在另一个空间出现的最后一个位置 */
// 为了能够双向查找，SGI将算法设计成双层架构
// 上层函数 dispatch function(分派函数)
// 版本1
template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
  typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
  typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;
  
  // 根据两个区间的类别，调用不同的下层函数
  return __find_end(first1, last1, first2, last2, category1(), category2());
}

// 这是一种常见的技巧，在函数调用的过程中产生迭代器类型的临时对象，再利用参数推导机制自动调用某个对应的函数

// forward iterator 版本
template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag) {
  if(first1 == first2)
    return last1;
  else{
    ForwardIterator1 result = last1;
    while(1){
      // 底层竟然用的search，它也不是用啥复杂的方法从后往前整，就很朴素的一个一个查
      // 这个迭代器不能反向查找
      ForwardIterator1 new_result = search(first1, last1, first2, last2);
      if(new_result == last1)
        return result;
      else{
        result = new_result;
        first1 = new_result;
        ++first1;
      }
    }
  }
}
// bidirectional iterator 版本
template <class BidirectionalIterator1, class BidirectionalIterator2>
inline BidirectionalIterator1 __find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1, BidirectionalIterator2 first2, BidirectionalIterator2 last2, bidirectional_iterator_tag, bidirectional_iterator_tag) {
  // 它可以反向查找
  typedef reverse_iterator<BidirectionalIterator1> reviter1;
  typedef reverse_iterator<BidirectionalIterator2> reviter2;

  reviter1 rlast1(first1);
  reviter2 rlast2(first2);

  // 逆转序列1序列2
  reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);

  if(rresult == rlast1)
    return last1;
  else{
    // 这里的逆转迭代器要在后面学习
    BidirectionalIterator1 result = rresult.base(); // 转回逆转前状态
    advance(result, -distance(first2, last2)); // 调整到子序列的起始处
    return result;
  }
}
// 那么它的版本二(允许用户指定仿函数)如何实现呢？

/* 查找一个空间在另一个空间出现的第一个位置 */
// 版本1
template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2) {
  for( ; first1 != last1; ++first1)
    for(ForwardIterator iter = first2; iter != last2; ++iter)
      if(*first1 == *iter)
        return first1;
  return last1;
}

// 版本2
template <class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp) {
  for( ; first1 != last1; ++first1)
    for(ForwardIterator iter = first2; iter != last2; ++iter)
      if(comp(*first1, *iter))
        return first1;
  return last1;
}