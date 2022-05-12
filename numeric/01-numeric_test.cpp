#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
using namespace std;

int main()
{
  int ia[5] = {1, 2, 3, 4, 5};
  vector<int> iv(ia, ia+5);

  cout << accumulate(iv.begin(), iv.end(), 0) << endl;
  // 15, i.e. 0 + 1 + 2 + 3 + 4 + 5

  cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;
  // -15, i.e. 0 - 1 - 2 - 3 - 4 - 5

  cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
  // 65, i.e. 10 + 1*1 + 2*2 + 3*3 + 4*4 + 5*5

  cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;
  // -20, i.e. 10 - 1+1 - 2+2 - 3+3 - 4+4 - 5+5

  // ostream_iterator作为输出工具(可以把它想象成一个绑定到屏幕的迭代器，型别吻合的数据丢进来就会被显示到屏幕)
  ostream_iterator<int> oite(cout, " ");

  partial_sum(iv.begin(), iv.end(), oite);
  // 1 3 6 10 15 (第n个新元素是前n个旧元素的相加总计)

  partial_sum(iv.begin(), iv.end(), oite, minus<int>());
  // 1 -1 -4 -8 -13 (第n个新元素=第一个旧元素-前n-1个旧元素的总计)

  adjacent_difference(iv.begin(), iv.end(), oite);
  // 1 1 1 1 1 (第一个元素照旧，第n个新元素=第n个旧元素-第n-1个旧元素)

  adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
  // 1 3 5 7 9 (第一个元素照旧，第n个新元素 = op(第n个旧元素,第n-1个旧元素))

  cout << power(10, 3) << endl;
  // 1000, i.e. 10*10*10
  cout << power(10, 3, plus<int>()) << endl;
  // 30, i.e. 10+10+10

  int n=3;
  iota(iv.begin(), iv.end(), n); // 在指定区间内填入n，n+1，n+2...
  for(int i=0;i<iv.size();++i)
    cout << iv[i] << ' '; // 3 4 5 6 7
}