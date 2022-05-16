/* next_permutation */
// 版本1
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
  if(first == last)
    return false;
  BidirectionalIterator i = first;
  ++i;
  if(i==last)
    return false;
  i=last;
  --i;
  for(;;){
    BidirectionalIterator ii = i;
    --i;
    if(*i<*ii){
      BidirectionalIterator j = last;
      while(!(*i<*--j));
      iter_swap(i,j);
      reverse(ii,last);
      return true;
    }
    if(i==first){ // 它没有下一个了，它是最后的
      reverse(first,last); // 这里还要逆转它？
      return false;
    }
  }
}

// 版本2
template <class BidirectionalIterator, class Compare>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
  if(first == last)
    return false;
  BidirectionalIterator i = first;
  ++i;
  if(i==last)
    return false;
  i=last;
  --i;
  for(;;){
    BidirectionalIterator ii = i;
    --i;
    if(comp(*i, *ii)){
      BidirectionalIterator j = last;
      while(!(comp(*i, *--j)));
      iter_swap(i,j);
      reverse(ii,last);
      return true;
    }
    if(i==first){ // 它没有下一个了，它是最后的
      reverse(first,last); // 这里还要逆转它？
      return false;
    }
  }
}

/* prev_permutation */
// 版本1
template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
  if(first == last)
    return false;
  BidirectionalIterator i = first;
  ++i;
  if(i==last)
    return false;
  i=last;
  --i;
  for(;;){
    BidirectionalIterator ii = i;
    --i;
    if(*ii<*i){
      BidirectionalIterator j = last;
      while(!(*--j<*i));
      iter_swap(i,j);
      reverse(ii,last);
      return true;
    }
    if(i==first){ // 它没有下一个了，它是最后的
      reverse(first,last); // 这里还要逆转它？
      return false;
    }
  }
}

// 版本2
template <class BidirectionalIterator, class Compare>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp) {
  if(first == last)
    return false;
  BidirectionalIterator i = first;
  ++i;
  if(i==last)
    return false;
  i=last;
  --i;
  for(;;){
    BidirectionalIterator ii = i;
    --i;
    if(comp(*ii, *i)){
      BidirectionalIterator j = last;
      while(!(comp(*--j, *i)));
      iter_swap(i,j);
      reverse(ii,last);
      return true;
    }
    if(i==first){ // 它没有下一个了，它是最后的
      reverse(first,last); // 这里还要逆转它？
      return false;
    }
  }
}