/*
这是逐渐泛化的过程
*/

// 1.这是一个普通的find()函数
// 它在限定区间内查找value
int* find(int* arrayHead, int arraySize, int value){
  int i;
  for(;i<arraySize; ++i)
    if(arrayHead[i]==value)
      break;
  return &(arrayHead[i]);
}

// 2.操作抽象化一些
int* find(int* begin, int* end, int value){
  while(begin!=end && *begin!=value)
    ++begin;
  return begin;
}

// 3.template
// value数值的传递从by value到by reference，降低传递的成本
// 使用const修饰，以防止它改变了原值
template <class T>
T* find(T* begin, T* end, const T& value){
  while(begin!=end && *begin!=value)
    ++begin;
  return begin;
}

// 4.将他转变为对象
// 这就有了迭代器的观念
#include <iterator>
template <class Iterator, class T>
Iterator find(Iterator begin, Iterator end, const T& value) {
  while(begin!=end && *begin!=value)
    ++begin;
  return begin;
}


#include <iostream>
using namespace std;

void main()
{
  const int arraySize = 7;
  int ia[arraySize] = {0,1,2,3,4,5,6};
  int* end = ia + arraySize;
  // 1.
  // 这样的find()暴露了容器的实现细节(第二个参数)，而且太过依赖容器
  int* ip = find(ia, sizeof(ia)/sizeof(int), 4);
  if(ip==end)
    cout << "4 not found" << endl;
  else
    cout << "4 found." << endl;

  // 2.
  int* ip = find(ia, end, 4);
  if(ip==end)
    cout << "4 not found" << endl;
  else
    cout << "4 found." << endl;

}