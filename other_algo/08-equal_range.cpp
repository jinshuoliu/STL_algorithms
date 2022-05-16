// 版本1
template <class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
  // 根据迭代器种类采取不同的策略
  return __equal_range(first, last, value, distance_type(first), iterato_category(first));
}

#include <iterator>
using namespace std;

// 版本1的random_access_iterator版本
template <class RandomAccessIterator, class T, class Distance>
pair<RandomAccessIterator, RandomAccessIterator> __equal_range(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag) {
  Distance len = last - first;
  Distance half;
  RandomAccessIterator middle, left, right;

  while(len>0) {
    half = len >> 1;
    middle = first+half;
    if(*middle<value){
      first = middle+1;
      len=len-half-1;
    }
    else if(value<*middle){
      len=half;
    }
    else { // 中间的元素等于指定值
      left = lower_bound(first, middle, value);
      right = upper_bound(++middle, first+len, value);
      return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
    }
  }
  // 在区间内没有找到等于value的位置，要返回大于value且最接近value的位置
  return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
  // 这个位置为什么是first呢？
  // while的最后一次，里面就一个元素了，在它不等于value的情况下它只能
  // 大于value，这里指向它的是first
  // 小于value，first指向它后面的元素，而这个元素比value大
}

// 版本1的forward_iterator版本
template <class ForwardIterator, class T, class Distance>
pair<ForwardIterator, ForwardIterator> __equal_range(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len);
  Distance half;
  ForwardIterator middle, left, right;

  while(len>0){
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if(*middle<value){
      first = middle;
      ++first;
      len=len-half-1;
    }
    else if(value<*middle){
      len=half;
    }
    else { // 中间的元素等于指定值
      left = lower_bound(first, middle, value);
      advance(first, len);
      right = upper_bound(++middle, first, value);
      return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
    }
  }
  return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}