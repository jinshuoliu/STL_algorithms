// 它的两个版本的差别在于随机数的取得不同
// 版本1：使用内部随机数产生器
template <class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
  __random_shuffle(first, last, distance_type(first));
}

template <class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance*) {
  if(first==last)
    return;
  for(RandomAccessIterator i = first + 1; i!= last; ++i)
#ifdef __STL_NO_RAND48
  iter_swap(i, first+Distance(rand()%((i-first)+1)));
#else
  iter_swap(i, first+Distance(lrand48()%((i-first)+1)));
#endif
}

// 版本2：使用一个会产生随机随机数的仿函数
// 该仿函数的传递方式是by reference，因为随机随机数产生器的重要特性：它拥有局部状态，每次调用时会改变
template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& rand) {
  if(first==last)
    return;
  for(RandomAccessIterator i = first + 1; i != last; ++i)
    iter_swap(i, first+rand((i-first)+1));
}