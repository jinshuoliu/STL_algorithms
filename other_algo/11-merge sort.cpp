template <class BidirectionalIter>
void mergesort(BidirectionalIter first, BidirectionalIter last) {
  typename iterator_traits<BidirectionalIter>::difference_type n = distance(first, last);
  if(n==0 || n==1) // 分割到不能分割的程度开始合并
    return;
  else{
    // 分割
    BidirectionalIter mid = first + n / 2;
    mergesort(first, mid);
    mergesort(mid, last);
    // 合并
    inplace_merge(first, mid, last);
  }
}