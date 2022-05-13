template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
  for( ; first != last; ++first)
    *first = gen();
}

template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
  for( ; n > 0; --n, ++first)
    *first = gen();
  return first;
}