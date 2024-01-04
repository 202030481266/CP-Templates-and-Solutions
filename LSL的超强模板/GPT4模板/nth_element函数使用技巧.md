```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for nth_element and accumulate

int main() {
    std::vector<int> v = { /* 你的数据 */ };
    
    // 只排序最小的五个元素
    std::nth_element(v.begin(), v.begin() + 4, v.end());

    // 计算最小五个数字的和
    int sum = std::accumulate(v.begin(), v.begin() + 5, 0);

    std::cout << "Sum of the five smallest numbers is: " << sum << std::endl;

    return 0;
}
```

在 C++ 中，`nth_element()` 是一个非常有用的函数，它是 C++ 标准库算法的一部分。此函数重排范围内的元素，使得指定位置（即第 n 个位置）的元素将会是如果范围内所有元素都排序后该位置上的元素，同时保证它之前的所有元素都不大于该位置的元素，而之后的所有元素都不小于它。

`nth_element` 函数的原型如下：
```cpp
template<class RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last);

template<class RandomIt, class Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp);
```

- `first` 和 `last` 分别是要重排序列的起始和结束迭代器。
- `nth` 是一个迭代器，指向序列中应该排序的位置。
- `comp` 是一个可选的比较函数，用于定义元素的排序标准。

例如，如果有一个包含 10 个元素的向量 `v`，并且你想找到第 5 个最小的元素（索引为 4），你可以这样使用 `nth_element`：
```cpp
std::nth_element(v.begin(), v.begin() + 4, v.end());
```

执行这个函数后，`v[4]` 将包含整个序列中第 5 个最小的元素，`v[0]` 到 `v[3]` 中的元素将是小于或等于 `v[4]` 的元素（未排序），`v[5]` 到 `v[9]` 中的元素将是大于 `v[4]` 的元素（未排序）。