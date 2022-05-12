# 算法

```txt
  01-generalize_test.cpp:泛化的例子
  numeric:关于数值算法的代码
    01-numeric_test.cpp:几个数值算法的运用实例
    02-accumulate.cpp:求和
    03-adjacent_difference.cpp:区间内相邻元素差值
    04-inner_product.cpp:两个区间对应位置乘积
    05-partial_sum.cpp:前n项和
    06-power.cpp:计算x的n幂次方
    07-itoa.cpp:让区间内呈现从value递增的状态
  numeric_base:numeric中常用的算法代码
    01-numeric_base_test.cpp:运用实例
    02-equal.cpp:比较区间内容
    03-fill.cpp:指定范围内填充指定值
    04-fill_n.cpp:从起始位置开始的n个元素填充指定值
    05-iter_swap.cpp:将两个ForwardIterators所指的对象对调
    06-lexicographical_compare.cpp:以字典排列方式对两个序列进行比较
    07-max.cpp:取大
    08-min.cpp:取小
    09-mismatch.cpp:比较两个序列，指出第一个不匹配点
    10-swap.cpp:交换两个对象内容
    11-copy.cpp:拷贝
    12-copy_test.cpp:测试不同情况下调用不同的拷贝函数
```

## 1. 概述

算法：以有限的步骤，解决逻辑或数学问题

### 1.1. 算法分析与复杂度

- 算法分析：
  - 计算该算法所使用的空间和时间资源的操作
- 一般情况执行时间与处理数据量有关
  - 一般为一次、二次、三次、对数
  - 固定时间为O(1)
- 复杂度标记法
  - Big-Oh：常用,但不适合用来标记小数据量的情况
  - Big-Omega
  - Big-Theta
  - Little-Oh

### 1.2. STL算法总览

|算法名称|算法用途|质变?|所在文件|
|--|--|--|--|
|accumulate|元素累计|否|<stl_numeric.h>|
|adjacent_difference|相邻元素的差额|是if in-place|<stl_numeric.h>|
|adjacent_find|查找相邻而重复(或符合条件)的元素|否|<stl_algo.h>|
|binary_search|二分查找|否|<stl_algo.h>|
|Copy|复制|是if in-place|<stl_algobase.h>|
|Copy_backward|逆向复制|是if in-place|<stl_algobase.h>|
|Copy_n *|复制n个元素|是if in-place|<stl_algobase.h>|
|count|计数|否|<stl_algo.h>|
|count_if|再特定条件下计数|否|<stl_algo.h>|
|equal|判断两个区间是否相等|否|<stl_algobase.h>|
|equal_range|试图再有序区间中寻找某值|否|<stl_algo.h>|
|fill|改填元素值|是|<stl_algobase.h>|
|fill_n|改填元素值(n次)|是|<stl_algobase.h>|
|find|循序查找|否|<stl_algo.h>|
|find_if|循序查找符合特定条件的|否|<stl_algo.h>|
|find_end|查找某个子序列的最后一次出现点|否|<stl_algo.h>|
|find_first_of|查找某些元素的首次出现点|否|<stl_algo.h>|
|for_each|对区间内的每个元素施行某操作|否|<stl_algo.h>|
|generate|以特定操作的运算结果填充特定区间的元素|是|<stl_algo.h>|
|generate_n|以特定操作的运算结果填充n个元素内容|是|<stl_algo.h>|
|includes|是否涵盖于某序列中|否|<stl_algo.h>|
|inner_product|内积|否|<stl_numeric.h>|
|inplace_merge|合并并就地替换|是|<stl_algo.h>|
|Iota *|在某区间填入某指定值的递增序列|是|<stl_numeric.h>|
|is_heap *|判断某区间是否为一个heap|否|<stl_algo.h>|
|is_sorted *|判断某区间是否已排序|否|<stl_algo.h>|
|iter_swap|元素互换|是|<stl_algobase.h>|
|lexicographical_compare|以字典顺序进行比较|否|<stl_numeric.h>|
|lower_bound|“将指定元素插入区间内而不影响区间原本的排序”的最低位置|否|<stl_algo.h>|
|max|最大值|否|<stl_algobase.h>|
|max_element|最大值的位置|否|<stl_algo.h>|
|merge|合并两个序列|是if in-place|<stl_algo.h>|
|min|最小值|否|<stl_algobase.h>|
|min_element|最小值的位置|否|<stl_algo.h>|
|mismatch|找出不匹配点|否|<stl_algobase.h>|
|next_permutation|获得下一个排列组合|是|<stl_algo.h>|
|nth_element|重新安排序列中的第n个元素的左右两端|是|<stl_algo.h>|
|partial_sort|局部排序|是|<stl_algo.h>|
|partial_sort_copy|局部排序并复制到它处|是if in-place|<stl_algo.h>|
|partial_sum|局部求和|是if in-place|<stl_numeric.h>|
|partition|分割|是|<stl_algo.h>|
|prev_permutation|获得前一个排列组合|是|<stl_algo.h>|
|power *|幂次方，可指定表达式|否|<stl_numeric.h>|
|random_shuffle|随机重排元素|是|<stl_algo.h>|
|random_sample *|随机取样|是if in-place|<stl_algo.h>|
|random_sample_n *|随机取样|是if in-place|<stl_algo.h>|
|remove|删除某类元素|是|<stl_algo.h>|
|remove_copy|删除某类元素并将结果复制到另一个容器|是|<stl_algo.h>|
|remove_if|有条件地删除某类元素|是|<stl_algo.h>|
|remove_copy_if|有条件地删除某类元素并将结果复制到另一个容器|是|<stl_algo.h>|
|replace|替换某类元素|是|<stl_algo.h>|
|replace_copy|替换某类元素，并将结果复制到另一个容器|是|<stl_algo.h>|
|replace_if|有条件地替换|是|<stl_algo.h>|
|replace_copy_if|有条件地替换，并将结果复制到另一个容器|是|<stl_algo.h>|
|reverse|反转元素次序|是|<stl_algo.h>|
|reverse_copy|反转元素次序并将结果复制到另一个容器|是|<stl_algo.h>|
|rotate|旋转|是|<stl_algo.h>|
|rotate_copy|旋转，并将结果复制到另一个容器|是|<stl_algo.h>|
|search|查找某个子序列|否|<stl_algo.h>|
|search_n|查找连续发生n次的子序列|否|<stl_algo.h>|
|set_difference|差集|是if in-place|<stl_algo.h>|
|set_intersection|交集|是if in-place|<stl_algo.h>|
|set_symmetric_difference|对称差集|是if in-place|<stl_algo.h>|
|set_union|并集|是if in-place|<stl_algo.h>|
|sort|排序|是|<stl_algo.h>|
|stable_partition|分割并保持元素的相对次序|是|<stl_algo.h>|
|stable_sort|排序并保持等值元素的相对次序|是|<stl_algo.h>|
|swap|交换|是|<stl_algobase.h>|
|swap_ranges|交换指定区间|是|<stl_algo.h>|
|transform|以两个序列为基础，交互作用产生第三个序列|是|<stl_algo.h>|
|unique|将重复的元素折叠缩编，使其成为唯一|是|<stl_algo.h>|
|unique_copy|将重读的元素折叠缩编，使其成为唯一，并复制到其他地方|是if in-place|<stl_algo.h>|
|upper_bound|“将指定元素插入区间内而不影响区间的原本排序”的最高位置|否|<stl_algo.h>|
|make_heap|制造一个heap|是|<stl_heap.h>|
|pop_heap|从heap取出一个元素|是|<stl_heap.h>|
|push_heap|将一个元素推进heap中|是|<stl_heap.h>|
|sort_heap|对heap排序|是|<stl_heap.h>|

### 1.3. 质变算法(mutating algorithms)

- 会改变操作对象的值
- STL的算法作用在迭代器[first,last)的区间内
  - 质变算法会改变区间内的元素内容
  - 例如：拷贝、互换、替换、填写、删除、排列组合、分割、随即重排、排序...

### 1.4. 非质变算法(nonmutating algorithms)

- 不改变操作对象的值
  - 例如：查找、匹配、计数、巡访、比较、寻找极值...

### 1.5. STL算法的一般形式

- 所有的泛型算法的前两个参数都是一对迭代器指向区间[first,last)
- STL的算法声明都表现出它所需要的最低程度的迭代器类型
  - STL有五类迭代器，前面讲了他们的关系
  - 将无效的迭代器给算法，不一定会在什么时期被捕抓
- STL算法不一定只支持一个版本
  - 可能是一个基础的，其他的再添加一些限制条件，或者额外参数
- 质变算法通常提供两个版本：
  - 一个是in-place版，就地改变其操作对象
  - 另一个是copy版，将操作对象的内容复制一个副本，改好后返回该副本(通常以_copy为函数名的结尾)
- 所有的数值算法都实现于<stl_numeric.h>之中
  - 这是个内部文件，必须包含上层的< numeric >
- 其他STL算法实现于<stl_algo.h>和<stl_algobase.h>之中
  - 他们也是内部文件，需要包含< algorithm >

## 2. 算法的泛化过程

- 将算法独立于其所处理的数据结构之外，不受数据结构的羁绊
- 泛化
  - 把操作对象的型别加以抽象化
  - 把操作对象的标示法和区间目标的移动行为抽象化
  - 整个算法也就在一个抽象层面上工作了
- 几乎所有的东西都可以改写为程序员自定义的形式或行为

## 3. 数值算法

- 数值算法都包含表头< numeric >,SGI将它实现于<stl_numeric.h>

### 3.1. accumulate

- 用来计算init和[first,last)内所有元素的总和
- 必须要有一个init，目的是当传进来的区间为空时能获得一个明确的值
- 里面的二元操作符不需要满足交换率和结合律

### 3.2. adjacent_difference

- 用来计算[first, last)中相邻元素的差额
  - 将 第i号元素-第i-1号元素 的值 赋给 第i-1号元素

### 3.3. inner_product

- 计算[first1,last1) 和 [first2, first2+(last1-first1)) 的内积
  - 区间2的大小必须大于等于区间1的大小

### 3.4. partial_sum

- 用来计算局部总和
  - 就是前n项求和

### 3.5. power

- 专属于SGI，用来计算某数的n幂次方
  - n幂次方：自己对自己进行某种运算，达到n次
  - 运算类型可由外界指定

### 3.6. itoa

- 专属于SGI，
  - 用来设定某个区间的内容，使其内的每个元素从指定的value开始，呈递增状态
  - 属于质变算法

## 4. 基本算法

- 常用的一些算法，包含在<stl_algobase.h>

### 4.1. equal

- 比较两个区间的内容是否相同，会有一些问题

### 4.2. fill

- 指定范围内填充指定值

### 4.3. fill_n

- 从起始位置开始的n个元素填充指定值
- 返回的迭代器执行被填入的最后一个元素的下一个位置
- 但是可能会超越容器的大小，造成不可预期的错误
  - 解决：使用inserter()产生一个具有插而非覆写能力的迭代器

### 4.4. iter_swap

- 将两个ForwardIterators所指的对象对调

### 4.5. lexicographical_compare

- 以字典排列(直接看ASCII码)方式对两个序列进行比较
  - 对应位置比较
  - 结束：
    - 有对应位置元素不等
    - 同时达到两区间边界
    - 到达某一区间边界
  - 结果：
    - 第一区间小，返回true
    - 到达第一区间边界，返回true
    - 同时到达两区间边界，返回false

### 4.6. max

- 取两个对象中的较大值

### 4.7. min

- 取两个对象中的较小值

### 4.8. mismatch

- 比较两个序列，指出第一个不匹配点
  - 返回一对迭代器(pair)，分别指向他们第一个不匹配的点
- 如果第一序列比第二序列的元素多，会发生不可预的错误

### 4.9. swap

- 交换两个对象的内容

### 4.10. copy

- 复制操作
  - 将输入区间[first,last)内的元素复制到输出区间[result, result+(last-first))内
    - 输入区间和输出区间叠加情况需要酌情考虑使用copy()还是copy_backward()
  - 返回迭代器指向输出区间的end
- 复制操作的两个方法
  - 运用assignment operator(copy就是用它)
  - 运用copy constructor

![copy](MD/assert/4-10-copy.png)

- 有些元素型别拥有的是trivial assignment operator
  - 如果能够使用内存直接复制行为就能节省很多时间(memmove或memcpy)
  - 为了达到目的，SGI STL用了很多方法
    - 函数重载
    - 型别特性
    - 偏特化

- copy更改的是输出区间中迭代器所指的对象
  - 并不会更改迭代器本身
  - copy不能将元素插入到空容器中

### 4.11. copy_backward

- 它与copy几乎完全一样
  - 区别：它是逆向复制，copy是正向复制
