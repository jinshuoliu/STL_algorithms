/* max */
// 版本1
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
  if(first == last)
    return first;
  ForwardIterator result = first;
  while(++first != last)
    if(*result < *first)
      result = first;
  return result;
}

// 版本2
template <class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
  if(first == last)
    return first;
  ForwardIterator result = first;
  while(++first != last)
    if(comp(*result, *first))
      result = first;
  return result;
}

/* min */
// 版本1
template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
  if(first == last)
    return first;
  ForwardIterator result = first;
  while(++first != last)
    if(*first < *result)
      result = first;
  return result;
}

// 版本2
template <class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
  if(first == last)
    return first;
  ForwardIterator result = first;
  while(++first != last)
    if(comp(*first, *result))
      result = first;
  return result;
}