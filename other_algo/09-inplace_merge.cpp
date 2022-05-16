template <class BidirectionalIterator>
inline void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last) {
  if(first == middle || middle == last)
    return;
  __inplace_merge_aux(first, middle, last, value_type(first), distance_type(first));
}

// 辅助函数
template <class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, T*, Distance*) {
  // 记录前后两块的长度
  Distance len1=0;
  distance(first, middle, len1);
  Distance len2=0;
  distance(middle, last, len2);

  // 该算法会使用额外的内存空间
  temporary_buffer<BidirectionalIterator, T> buf(first, last);
  if(buf.begin() == 0) // 内存配置失败
    __merge_without_buffer(first, middle, last, len1, len2);
  else // 可以配置内存
    __merge_adaptive(first, middle, last, len1, len2, buf.begin(), Distance(buf.size()));
}

// 可以配置内存的辅助函数
template <class BidirectionalIterator, class Distance, class Pointer>
void __merge_adaptive(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance len1, Distance len2, Pointer buffer, Distance buffer_size) {
  // 它的优先情况
  // 优先放置短的
  // 其次优先序列一
  if(len1<=len2 && len1 <= buffer_size){
    // 缓冲区足够盛放序列一
    Pointer end_buffer = copy(first, middle, buffer);
    // merge将两个有序但分离的两个区间合并
    merge(buffer, end_buffer, middle, last, first);
  }
  else if(len2<=buffer_size) {
    Pointer end_buffer = copy(middle, last, buffer);
    merge(first, middle, buffer, end_buffer, last);
  }
  else { // 当空间太小时
    // 以递归分割的方式让处理长度减半，再进行判断
    BidirectionalIterator first_cut = first;
    BidirectionalIterator second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if(len1>len2) { // 拿较长的序列开刀
      // len11记录len1的一半
      len11 = len1/2;
      // first_cut += len11;
      // first_cut 为前半部的中间
      advance(first_cut, len11);
      // 第二刀是后半部分第一刀可以插入的位置
      second_cut = lower_bound(middle, last, *first_cut);
      // distance计算距离，但是他这里要第三参数，那么是用第三参数来记录长度吗？
      // 那么len22记录的是middle到第二刀的位置
      distance(middle, second_cut, len22);
    }
    else {
      len22 = len2/2;
      advance(second_cut, len22);
      first_cut = upper_bound(first, middle, *first_cut);
      distance(first, first_cut, len11);
    }
    // 旋转操作，实际它就是前后两块互换位置，然后它是哪里和哪里呢？
    // 解读一下：
    // 第一刀位置到中间位置，安置到第二刀位置，长度为len1-len11，再把从第二刀向前长度为len22的放到前面
    // 位置1 第一刀 位置2 middle 位置三 第二刀 位置四
    // 就是位置2和位置3互换位置
    BidirectionalIterator new_middle = __rotate_adaptive(first_cut, middle, second_cut, len1-len11, len22, buffer, buffer_size);
    // 针对左段递归
    __merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
    // 针对右段递归
    __merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size);
  }
}

// 旋转操作,互换位置
template <class BidirectionalIterator1, class BidirectionalIterator2, class Distance>
BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first, BidirectionalIterator1 middle, BidirectionalIterator1 last, Distance len1, Distance len2, BidirectionalIterator2 buffer, Distance buffer_size) {
  BidirectionalIterator2 buffer_end;
  if(len1>len2 && len2<=buffer_size){
    buffer_end = copy(middle, last, buffer);
    copy_backward(first, middle, last);
    return copy(buffer, buffer_end, first);
  }
  else if(len1<=buffer_size){
    buffer_end = copy(first, middle, buffer);
    copy_backward(middle, last, first);
    return copy(buffer, buffer_end, last);
  }
  else {
    // 缓冲区实在不够，就使用rotate算法，不需要缓冲区
    rotate(first, middle, last);
    advance(first, len2);
    return first;
  }
}