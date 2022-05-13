template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2) {
  for(; first1 != last1; ++first1, ++first2)
    iter_swap(first1, first2);
  return first2;
}