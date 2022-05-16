/* lower_bound */
// 版本1的分派函数
template <class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value) {
  return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
}

#include <iterator>
using namespace std;

// 辅助函数 forward_iterator版本
template <class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len); // 获得区间长度,使用这个操作是因为迭代器不可以直接使用+-
  Distance half;
  ForwardIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if(*middle < value) {
      first = middle;
      ++first;
      len = len-half-1;
    }
    else
      len = half; // 判断的这个分支如此简单是因为它并不是指向头尾，而是指向头再记住长度
  }
  return first;
}

// 辅助函数 random_access_iterator版本
template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag) {
  Distance len = last-first;
  Distance half;
  RandomAccessIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first + half;
    if(*middle < value) {
      first = middle + 1;
      len = len-half-1;
    }
    else
      len = half;
  }
  return first;
}

// 版本2的分派函数
template <class ForwardIterator, class T, class Compare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
  return __lower_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

// 辅助函数 forward_iterator版本
template <class ForwardIterator, class T, class Compare, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len); // 获得区间长度,使用这个操作是因为迭代器不可以直接使用+-
  Distance half;
  ForwardIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if(comp(*middle, value)) {
      first = middle;
      ++first;
      len = len-half-1;
    }
    else
      len = half; // 判断的这个分支如此简单是因为它并不是指向头尾，而是指向头再记住长度
  }
  return first;
}

// 辅助函数 random_access_iterator版本
template <class RandomAccessIterator, class T, class Compare, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Compare comp, Distance*, random_access_iterator_tag) {
  Distance len = last-first;
  Distance half;
  RandomAccessIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first + half;
    if(comp(*middle, value)) {
      first = middle + 1;
      len = len-half-1;
    }
    else
      len = half;
  }
  return first;
}

/* upper_bound */
// 版本1的分派函数
template <class ForwardIterator, class T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value) {
  return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
}

// 辅助函数 forward_iterator版本
template <class ForwardIterator, class T, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len); // 获得区间长度,使用这个操作是因为迭代器不可以直接使用+-
  Distance half;
  ForwardIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if(*middle < value) {
      len = half; // 判断的这个分支如此简单是因为它并不是指向头尾，而是指向头再记住长度
    }
    else{
      first = middle;
      ++first;
      len = len-half-1;
    }
  }
  return first;
}

// 辅助函数 random_access_iterator版本
template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag) {
  Distance len = last-first;
  Distance half;
  RandomAccessIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first + half;
    if(*middle < value) {
      len = half;
    }
    else{
      first = middle + 1;
      len = len-half-1;
    }
  }
  return first;
}

// 版本2的分派函数
template <class ForwardIterator, class T, class Compare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
  return __upper_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

// 辅助函数 forward_iterator版本
template <class ForwardIterator, class T, class Compare, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag) {
  Distance len = 0;
  distance(first, last, len); // 获得区间长度,使用这个操作是因为迭代器不可以直接使用+-
  Distance half;
  ForwardIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first;
    advance(middle, half);
    if(*middle < value) {
      len = half; // 判断的这个分支如此简单是因为它并不是指向头尾，而是指向头再记住长度
    }
    else{
      first = middle;
      ++first;
      len = len-half-1;
    }
  }
  return first;
}

// 辅助函数 random_access_iterator版本
template <class RandomAccessIterator, class T, class Compare, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Compare comp, Distance*, random_access_iterator_tag) {
  Distance len = last-first;
  Distance half;
  RandomAccessIterator middle;

  while(len>0){
    half = len >> 1;
    middle = first + half;
    if(*middle < value) {
      len = half;
    }
    else{
      first = middle + 1;
      len = len-half-1;
    }
  }
  return first;
}
