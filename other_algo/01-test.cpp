#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

struct even {
  bool operator()(int x) const {
    return x%2 ? false : true;
  }
};

int main()
{
  int ia[] = {12, 17, 20, 22, 23, 30, 33, 40};
  vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));

  cout << *lower_bound(iv.begin(), iv.end(), 21) << endl; // 22
  cout << *upper_bound(iv.begin(), iv.end(), 21) << endl; // 22
  cout << *lower_bound(iv.begin(), iv.end(), 22) << endl; // 22
  cout << *upper_bound(iv.begin(), iv.end(), 22) << endl; // 23

  // 对于有序区间，使用二分查找
  cout << binary_search(iv.begin(), iv.end(), 33) << endl; // 1
  cout << binary_search(iv.begin(), iv.end(), 34) << endl; // 0
  
  // 下一个排列组合
  next_permutation(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 17 20 22 23 30 40 33

  // 上一个排列组合
  prev_permutation(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 17 20 22 23 30 33 40

  // 随机重排
  random_shuffle(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 33 12 30 20 22 17 23 40

  // 部分元素排序
  partial_sort(iv.begin(), iv.begin()+4, iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 17 20 22 33 30 23 40

  // 排序(递增)
  sort(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 17 20 22 23 30 33 40

  // 排序(按相应规定，此时规定为递减)
  sort(iv.begin(), iv.end(), greater<int>());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 40 33 30 23 22 20 17 12

  iv.push_back(22);
  iv.push_back(30);
  iv.push_back(17);

  // 排序，并保持原相对位置
  stable_sort(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 17 17 20 22 22 23 30 30 33 40

  // 对于一个有序区间，找到其中的子区间，它的每个元素都与某个特定元素值相同
  // 返回该子区间的头尾
  // 如果不存在这样的子区间返回的两个迭代器均指向该特定元素可以插入的位置
  pair<vector<int>::iterator, vector<int>::iterator> pairIte;
  pairIte = equal_range(iv.begin(), iv.end(), 22);
  // 找到
  cout << *(pairIte.first) << endl; // 22
  cout << *(pairIte.second) << endl; // 23

  pairIte = equal_range(iv.begin(), iv.end(), 25);
  // 未找到
  cout << *(pairIte.first) << endl; // 30
  cout << *(pairIte.second) << endl; // 30

  random_shuffle(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 33 12 30 20 22 17 23 40

  // 将小于某位置的元素置于该元素左侧，其余置于右侧，不保证原来的相对位置
  nth_element(iv.begin(), iv.begin()+4, iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 12 20 17 22 33 23 30 40

  // 将大于某位置的元素置于该元素左侧
  nth_element(iv.begin(), iv.begin()+4, iv.end(), greater<int>());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 33 23 30 40 22 12 20 17

  // 符合条件放在左侧，不符合放在右侧,可保障原相对位置
  stable_partition(iv.begin(), iv.end(), even());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  // 33 23 30 40 22 12 20 17
}