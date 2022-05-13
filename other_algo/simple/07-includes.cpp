// 版本1
template <class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
  while(first1 != last1 && first2 != last2)
    if(*first2 < * first1)
      return false;
    else if(*first1 < *first2)
      ++first1;
    else
      ++first1, ++first2;
  
  return first2 == last2;
}

// 版本2
template <class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
  while(first1 != last1 && first2 != last2)
    if(comp(*first2, * first1))
      return false;
    else if(comp(*first1, *first2))
      ++first1;
    else // 其实这里的else应该是else if(*first1 == *first2)的情况，那么使用了comp之后else还能代表它原来的意义吗？
      ++first1, ++first2;
  
  return first2 == last2;
}