#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

template <class T>
struct display {
  void operator()(const T& x) const {
    cout << x << ' ';
  }
};

int main()
{
  int ia[9] = {0,1,2,3,4,5,6,7,8};
  vector<int> iv1(ia, ia+5);
  vector<int> iv2(ia, ia+9);
  
  cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first); // end
  cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second); // 5
  // 判断两个区间的第一个不匹配点，返回一个由两个迭代器组成的pair
  // 第一个迭代器指向第一区间的不匹配点
  // 第二个迭代器指向第二区间的不匹配点
  // 应该先判断迭代器是否不等于容器的end()，然后再考虑输出

  cout << equal(iv1.begin(), iv1.end(), iv2.begin()); // 1, true
  cout << equal(iv1.begin(), iv1.end(), &ia[3]); // 0, false
  // 判断两个区间相同长度的内容是否相等，相等返回1，不等返回0
  // 第一个区间限定范围，第二个只给出起始边界，结束边界由第一个区间的长度来限定
  // 要是第二个区间的长度不足呢？
  cout << equal(iv1.begin(), iv1.end(), &ia[3], less<int>());
  // 指定比较方式

  fill(iv1.begin(), iv1.end(), 9);
  // 区间全部填入指定内容(9)
  for_each(iv1.begin(), iv2.end(), display<int>()); // 9 9 9 9 9 (遍历)

  fill_n(iv1.begin(), 3, 7);
  // 区间指定起始位置和长度全部填入指定内容(7)
  // 但是可能会超越容器的大小，造成不可预期的错误
  fill_n(inserter(iv1, iv1.begin()), 5, 7);
  // 解决：使用inserter()来产生一个插入能力的迭代器
  for_each(iv1.begin(), iv2.end(), display<int>()); // 7 7 7 9 9 (遍历)
  
  vector<int>::iterator ite1 = iv1.begin(); // 指向7
  vector<int>::iterator ite2 = ite1;
  advance(ite2, 3); // 指向9

  iter_swap(ite1, ite2); // 将两个迭代器所指元素对调
  cout << *ite1 << ' ' << * ite2 << endl; // 9 7
  for_each(iv1.begin(), iv1.end(), display<int>()); // 9 7 7 7 9 (对调后的结果) 

  // 取最大值
  cout << max(*ite1, *ite2) << endl;
  // 取最小值
  cout << min(*ite1, *ite2) << endl;

  // 取两个迭代器本身的最大最小值，没比较意义
  cout << *max(ite1, ite2) << endl;
  cout << *min(ite1, ite2) << endl;

  // 运行前：iv1:{9 7 7 7 9}，iv2:{0 1 2 3 4 5 6 7 8}
  swap(*iv1.begin(), *iv2.begin());
  for_each(iv1.begin(), iv1.end(), display<int>()); // 0 7 7 7 9
  for_each(iv2.begin(), iv2.end(), display<int>()); // 0 1 2 3 4 5 6 7 8

  string stra1[] = { "Jamie", "JJHou", "Jason"};
  string stra2[] = { "Jamie", "JJhou", "Jerry"};
  cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2);
  // 1 stra1 小于 stra2
  cout << lexicographical_compare(stra1, stra1+2, stra2, stra2+2, greater<string>());
  // 0 stra1 不大于 stra2
}