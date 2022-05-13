// 分派函数
template <class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last) {
  if(first == middle || middle == last)
    return;
  __rotate(first, middle, last, distance_type(first), iterator_category(first));
}
#include <iterator>
using namespace std;

// forward iterator版
template <class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag) {
  for(ForwardIterator i = middle; ;) {
    // 直接生硬交换
    iter_swap(first, i);
    ++first;
    ++i;
    if(first == middle){ // 前半部交换完毕
      if(i == last) // 后半部交换也完成
        return;
      middle = i;
    }
    else if(i == last) // 只有后半部交换完毕
      i = middle;
  }
}

// bidirectional iterator版
template <class BidirectionalIterator, class Disatnce>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Disatnce*, bidirectional_iterator_tag) {
  // 先旋转前半部
  reverse(first, middle);
  // 再旋转后半部
  reverse(middle, last);
  // 最后旋转整体
  reverse(first, last);
}

// random access iterator版
// 它是循环赋值，在复杂度上要简单一些
template <class RandomAccessIterator, class Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Distance*, random_access_iterator_tag) {
  // 取全长和前半部长的最大公因子
  Distance n = __gcd(last - first, middle - first);
  while(n--)
    __rotete_cycle(first, last, first + n, middle - first, value_type(first));
}

// 利用辗转相除法计算最大公因子
template <class EuclideanRingElement>
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n) {
  while (n != 0){
    EuclideanRingElement t = m % n;
    m=n;
    n=t;
  }
  return m;
}

template <class RandomAccessIterator, class Distance, class T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator initial, Distance shift, T*) {
  T value = *initial;
  RandomAccessIterator ptr1 = initial;
  RandomAccessIterator ptr2 = ptr1 + shift;
  while(ptr2 != initial) {
    *ptr1 = *ptr2;
    ptr1 = ptr2;
    if(last-ptr2>shift)
      ptr2 += shift;
    else
      ptr2 = first+(shift-(last-ptr2));
  }
  *ptr1 = value;
}

/* rotate_copy */
template <class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result) {
  return copy(first, middle, copy(middle, last, result));
}