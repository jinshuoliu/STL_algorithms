// 版本1
// 乘幂
template <class T, class Integer>
inline T power(T x, Integer n) {
  return power(x, n, multiples<T>()); // 指定运算形式为乘法
}

// 版本2
// 幂次方，如果指定为乘法，则当n>=0时返回x^n
// MonoidOperation 必须满足结合律，不需要满足交换律
template <class T, class Integer, class MonoidOperation>
inline T power(T x, Integer n, MonoidOperation op) {
  if (n==0)
    return identity_element(op);
  else { //偶数和奇数两种不同的处理方式，通过位移运算
    while ((n&1)==0) { // 偶数
      n >>= 1;
      x = op(x, x);
    }
    T result = x;
    n >>= 1;
    while(n != 0) { // 奇数
      x = op(x, x);
      if((n&1)!=0)
        result = op(result, x);
      n >>= 1;
    }
    return result;
  }
}
