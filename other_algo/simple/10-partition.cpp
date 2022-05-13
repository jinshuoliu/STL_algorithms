template <class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
  while(true) {
    while(true)
      if(first == last)
        return first;
      else if(pred(*first))
        ++first;
      else
        break;
    --last;
    while(true)
      if(first == last)
        return first;
      else if(!pred(*last))
        --last;
      else
        break;
    // 到这里就有了一个first和一个last都不符合条件了
    // 交换这两个元素
    iter_swap(first, last);
    ++first;
  }
}