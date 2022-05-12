// 完全泛化版本
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
  return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}

#include <cstring>
/*
两个重载函数是针对原生指针的
*/
// 重载版本1，针对const char*
inline char* copy(const char* first, const char* last, char* result) {
  memmove(result, first, last-first);
  return result+(last-first);
}

// 重载版本2，针对const wchar_t*
inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result) {
  memmove(result, first, sizeof(wchar_t) * (last-first));
  return result+(last-first);
}
/*
泛化版本调用的__copy_dispatch()函数有三个版本
*/
// 完全泛化版本
template <class InputIterator, class OutputIterator>
struct __copy_dispatch {
  OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
    return __copy(first, last, result, iterator_category(first));
  }
};

// 偏特化版本1，两个参数都是T*指针形式
template <class T>
struct __copy_dispatch<T*, T*> {
  T* operator()(T* first, T* last, T* result) {
    typedef typename __type_traits<T>::has_trivial_assignment_operator t;
    return __copy_t(first, last, result, t());
  }
};

// 偏特化版本2，第一参数为const T*指针形式，第二参数为T*指针形式
template <class T>
struct __copy_dispatch<const T*, T*> {
  T* operator()(T* first, T* last, T* result) {
    typedef typename __type_traits<T>::has_trivial_assignment_operator t;
    return __copy_t(first, last, result, t());
  }
};

/*
__copy_dispatch()的完全泛化版本根据迭代器种类不同，调用不同的__copy(),会有快慢之别
*/
#include <iterator>
// InputIterator 版本
template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag) {
  for(; first != last; ++result, ++first)
    *result = *first; // assifnment operator
  return result;
}

// RandomAccessIterator 版本
template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, std::random_access_iterator_tag) {
  return __copy_d(first, last, result, distance_type(first));
}

template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*) {
  for(Distance n = last-first; n > 0; --n, ++result, ++first)
    *result = *first; // assifnment operator
  return result;
}

/*
两个偏特化版本在“参数是原生指针形式”的前提下进一步探测
指针所指之物是否具有trival assignment oerator(平凡复制操作符)
STL通过__type_traits<>编程技巧来弥补
*/
using namespace std;
// 指针所指对象具备 trivial assignment operator
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type) {
  memmove(result, first, sizeof(T) * (last - first));
  return result + (last-first);
}

// 指针所指对象具备 non-trivial assignment operator
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type) {
  return __copy_d(first, last, result, (ptrdiff_t*)0);
}

