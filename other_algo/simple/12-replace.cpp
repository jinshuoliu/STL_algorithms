/* replace */
template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
  for(; first != last; ++first)
    if(*first == old_value)
      *first = new_value;
}

/* replace_copy */
template <class ForwardIterator, class OutputIterator, class T>
void replace_copy(ForwardIterator first, ForwardIterator last, OutputIterator result, const T& old_value, const T& new_value) {
  for(; first != last; ++first, ++result)
      *result = *first == old_value ? new_value : *first;
  return result;
}

/* replace_if */
template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value) {
  for(; first != last; ++first)
    if(pred(*first))
      *first = new_value;
}

/* replace_copy_if */
template <class ForwardIterator, class OutputIterator, class Predicate, class T>
void replace_copy_if(ForwardIterator first, ForwardIterator last, OutputIterator result, Predicate pred, const T& new_value) {
  for(; first != last; ++first, ++result)
      *result = pred(*first) ? new_value : *first;
  return result;
}