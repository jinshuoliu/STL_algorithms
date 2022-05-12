template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
  for(;first1!=last1 && first2!=last2; ++first1, ++first2) {
    if(*first1<*first2)
      return true;
    if(*first2<*first1)
      return false;
  }
  // 如果进行到尾端了，就要看看符合哪种条件了
  return first1==last1 && first2!=last2;
}

// 允许指定仿函数进行比较操作
template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
  for(;first1!=last1 && first2!=last2; ++first1, ++first2) {
    if(comp(*first1, *first2))
      return true;
    if(comp(*first2, *first1))
      return false;
  }
  return first1==last1 && first2!=last2;
}

#include <cstring>
#include <algorithm>
// SGI设计的特化版本，用于原生指针
inline bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2) {
  const size_t len1 = last1 - first1;
  const size_t len2 = last2 - first2;
  // memcmp()：C标准函数，以unsigned char的方式来比较两序列中一一对应的每一个bytes
  const int result = memcmp(first1, first2, std::min(len1, len2));
  return result != 0 ? result < 0 : len1 < len2;
}