#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
using namespace std;

class C {
public:
  C() : _data(3) {}
  // there is a trivial assignment operator
private:
  int _data;
};

int main()
{
  // 1
  const char ccs[5] = {'a', 'b', 'c', 'd', 'e'}; // 数据来源
  char ccd[5]; // 数据去处
  copy(ccs, ccs+5, ccd);
  // 调用版本是copy(const char*)

  // 2
  const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'}; // 数据来源
  wchar_t cwcd[5]; // 数据去处
  copy(cwcs, cwcs+5, cwcd);
  // 调用版本是copy(const wchar_t*)

  // 3
  int ia[5] = {0,1,2,3,4};
  copy(ia, ia+5, ia); // 来源于去处相同
  // 调用版本
  // copy()
  //  __copy_dispatch(T*, T*)
  //    __copy_t(__true_type)

  // 4
  // list的迭代器是InputIterator
  list<int> ilists(ia, ia+5); // 来源
  list<int> ilistd(5); // 去处
  copy(ilists.begin(), ilists.end(), ilistd.begin());
  // 调用版本
  // copy()
  //  __copy_dispatch()
  //    __copy(input_iterator)

  // 5
  // vector迭代器是原生指针
  vector<int> ivecs(ia, ia+5);
  // 5 6 会产生输出信息，因为：调用的vector ctor调用了copy()
  // 输出信息：
  // copy()
  //  __copy_dispatch(T*, T*)
  //    __copy_t(__true_type)
  // 原因，追踪vector ctor
  // vector<T>::vector(first, last)
  //  vector<T>::allocate_and_copy(n, first, last)
  //    ::uninitialized_copy(first, last, result)
  //      ::__uninitialized_copy(first, last, result, value_type(result))
  //        ::__uninitialized_copy_aux(first, last, result, is_POD())
  //          ::copy(first, last, result)
  vector<int> ivecd(5);
  copy(ivecs.begin(), ivecs.end(), ivecd.begin());
  // copy()
  //  __copy_dispatch(T*, T*)
  //    __copy_t(__true_type)
  // 完成copy后为什么不走random access iterator，而走T*
  // 因为vector迭代器是原生指针


  // 6
  // class C 具有 trivial operator=
  C c[5];
  vector<C> Cvs(c, c+5);
  // 同5
  vector<C> Cvd(5);
  copy(Cvs.begin(), Cvs.end(), Cvd.begin());
  // copy()
  //  __copy_dispatch(T*, T*)
  // 完成copy后为什么不走random access iterator，而走T*
  // 因为vector迭代器是原生指针
  //    __copy_t(__false_type)
  // 元素型别是trivial operator=为什么走__false_type？
  // 因为编译器中有能力验证“用户自定义型别”之型别特性的很少，所以大多数情况下都被认定为non-trivial operator
  //      __copy_d()

  // 7
  // deque迭代器别归纳为random access iterator
  deque<C> Cds(c, c+5);
  deque<C> Cdd(5);
  copy(Cds.begin(), Cds.end(), Cdd.begin());
  // copy()
  //  __copy_dispatch()
  //    __copy(random_access_iterator)
  //      __copy_d()

}