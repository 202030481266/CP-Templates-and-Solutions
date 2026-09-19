# 异或线性基 XorBasis

[模板源码](../../../data_structures/xor_basis.hpp) · [完整示例](../../../examples/data_structures/xor_basis.cpp) · [使用手册索引](../README.md)

从若干数中任取一个子集做异或，用线性基查询能否表示某个值、最大异或和、去重后的第 k 小异或和。本模板允许空子集，因此 0 总在可表示集合中。

## 接口和使用顺序

| 接口 | 含义 |
| --- | --- |
| `insert(x)` | 插入 uint64_t；增加秩返回 true，否则返回 false，O(64)。 |
| `contains(x)` | 是否可由已插入元素的某个子集异或得到，O(64)。 |
| `max_xor(initial=0)` | 最大化 initial XOR 子集异或值，O(64)。 |
| `kth(k)` | 去重后第 k 小，k 从 0 开始；optional<uint64_t>，无解为 nullopt，O(64²)。 |
| `rank()` | 独立基向量个数；可表示值的数量在数学上为 2^rank。 |

## 完整例子

下面是可以直接编译的完整程序，数据写在代码里，**不需要输入**。在 VS Code 打开对应 `.cpp` 后按 **Ctrl+Shift+B** 即可运行。

```cpp
#include <cstdint>
#include <iostream>
#include "data_structures/xor_basis.hpp"

int main() {
    cp::XorBasis basis;
    basis.insert(3);
    basis.insert(5);
    std::cout << std::boolalpha;
    std::cout << "independent(6)=" << basis.insert(6) << '\n';
    std::cout << "rank=" << basis.rank() << '\n';
    std::cout << "contains(6)=" << basis.contains(6)
              << " contains(1)=" << basis.contains(1) << '\n';
    std::cout << "maximum=" << basis.max_xor() << '\n';
    std::cout << "sorted:";
    for (std::uint64_t k = 0; k < 4; ++k) {
        if (auto value = basis.kth(k)) std::cout << ' ' << *value;
    }
    std::cout << '\n';
    std::cout << "kth(4)_exists=" << basis.kth(4).has_value() << '\n';
    std::cout << "with_initial_2=" << basis.max_xor(2) << '\n';
}
```

### 预期标准输出

```text
independent(6)=false
rank=2
contains(6)=true contains(1)=false
maximum=6
sorted: 0 3 5 6
kth(4)_exists=false
with_initial_2=7
```

## 注意事项

- 是“任选多个数”的异或；只允许选一个数时应该用 BinaryTrie。
- `kth(0)=0`。题目要求非空子集时，要另外判断是否存在非空子集异或为 0。
- 满秩 64 时，不要在调用端计算 `1ULL << 64`；kth 本身已处理这个边界。
- 先判断 optional 是否有值再解引用，不能用 UINT64_MAX 当作无解标记。

也可以在仓库根目录执行：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File cp-stl/tools/cp.ps1 -Action Run -Source "cp-stl/examples/data_structures/xor_basis.cpp"
```
