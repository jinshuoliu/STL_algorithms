// 分派函数
template <class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
  // 全部交给底层的函数
  __reverse(first, last, iterator_category(first));
}

#include <iterator>
using namespace std;

// bidirectional iterator版
template <class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag){
  while (true)
    if(first == last || first == --last)
      return;
    else
      iter_swap(first++, last);
  // 为什么它不能像下面那个那样直接操作呢？
  // BidirectionalIterator不能比较大小
}

// random access iterator
template <class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
  while(first < last)
    // 就是单纯的重复交换
    iter_swap(first++, --last);
}

/* reverse_copy */
template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result) {
  while(first != last) {
    --last;
    *result = *last;
    ++result;
  }
  return result;
}