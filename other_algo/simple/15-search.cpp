// 版本1
template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
{
  return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
}

template <class ForwardIterator1, class ForwardIterator2, class Distance1, class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, Distance1 *, Distance2 *)
{
  Distance1 d1 = 0;
  distance(first1, last1, d1);
  Distance2 d2 = 0;
  distance(first2, last2, d2);

  // 如果第二序列大于第一序列，那么第二序列不会是第一序列的子序列
  if (d1 < d2)
    return last1;

  ForwardIterator1 current1 = first1;
  ForwardIterator2 current2 = first2;

  while (current2 != last2)
    if (*current1 == *current2)
    {
      ++current1;
      ++current2;
    }
    else
    {
      // 每次都确定一下剩余的长度
      if (d1 == d2)
        return last1;
      else
      {
        current1 = ++first1;
        current2 = first2;
        --d1;
      }
    }
  return first1;
}

/* search_n */
// 版本1
template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T &value)
{
  if (count <= 0)
    return first;
  else
  {
    first = find(first, last, value);
    while (first != last)
    {
      Integer n = count - 1;
      ForwardIterator i = first;
      ++i;
      while (i != last && n != 0 && *i == value)
      {
        ++i;
        --n;
      }
      if (n == 0)
        return first;
      else
        // 这就是为了应对那种出现了部分目标的情况，剩下的不符合了，需要往后继续找
        first = find(i, last, value);
    }
    return last;
  }
}

// 版本2
template <class ForwardIterator, class Integer, class T, class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T &value, BinaryPredicate binary_pred)
{
  if (count <= 0)
    return first;
  else
  {
    // 同版本1的：first = find(first, last, value);
    while (first != last)
    {
      if (binary_pred(*first, value))
        break;
      ++first;
    }
    while (first != last)
    {
      Integer n = count - 1;
      ForwardIterator i = first;
      ++i;
      while (i != last && n != 0 && *i == value)
      {
        ++i;
        --n;
      }
      if (n == 0)
        return first;
      else
      {
        // 等同：first = find(i, last, value);
        while (i != last)
        {
          if (binary_pred(*i, value))
            break;
          ++i;
        }
        first = i;
      }
    }
    return last;
  }
}