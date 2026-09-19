# CP-STL：常用算法模板

先从下面的常用表找算法，打开对应头文件，复制或引用即可。每种算法只留一套明确接口；模板与可运行示例分开。

- **开始写题**：[template.cpp](template.cpp)，或在 C++ 文件中输入 `cpstart` 后选择代码片段。
- **配置与运行**：[VS Code 使用说明](docs/vscode.md)。
- **常见写法与进阶入口**：[使用示例 / DP 提示 / ACL](docs/recipes.md)。
- **旧文件去向及接口变化**：[迁移说明](docs/migration.md)。

## 先记住这 8 个入口

| 需求 | 文件 | 最常用接口 |
| --- | --- | --- |
| 二分答案、负数整除 | [basic/search.hpp](basic/search.hpp) | `first_true(lo, hi, check)`、`floor_div`、`ceil_div` |
| 连通性 | [data_structures/dsu.hpp](data_structures/dsu.hpp) | `DSU(n)`、`merge(u,v)`、`same(u,v)` |
| 单点加、区间和、第 k 小 | [data_structures/fenwick.hpp](data_structures/fenwick.hpp) | `add(p,x)`、`sum(l,r)`、`lower_bound(k)` |
| 单点修改、区间合并 | [data_structures/segment_tree.hpp](data_structures/segment_tree.hpp) | `set(p,x)`、`prod(l,r)`、`max_right(l,pred)` |
| 静态区间最值 / gcd | [data_structures/sparse_table.hpp](data_structures/sparse_table.hpp) | `SparseTable<T,Min/Max/Gcd>`、`query(l,r)` |
| BFS / 01 BFS / Dijkstra | [graph/shortest_path.hpp](graph/shortest_path.hpp) | `bfs`、`zero_one_bfs`、`dijkstra` |
| LCA、树上距离 | [graph/lca.hpp](graph/lca.hpp) | `lca(u,v)`、`distance(u,v)` |
| 模运算、组合数 | [math/combinatorics.hpp](math/combinatorics.hpp) | `Mint`、`Combinations<Mint>(n).choose(n,k)` |

## 一致的使用约定

1. **下标全部从 0 开始，区间全部为左闭右开 `[l,r)`**。题目给 1-based 闭区间 `[L,R]` 时，转换成 `[L-1,R)`。
2. 函数和类型位于 `namespace cp`。例如 `cp::DSU dsu(n);`。
3. 头文件支持 **GNU C++17 及以上**；仓库任务默认 C++20。少数数学/几何函数及主模板使用 GCC/Clang 的 `__int128`，不是 MSVC 模板。
4. 每个头文件都包含自己所需的头文件；有内部依赖时使用相对 `#include`，不需要预编译头、模块或 `import std`。
5. 图的邻接表只存真实的 `n` 个点。无向边要插入两次；Kruskal 的边列表每条无向边只存一次。
6. 和、距离、容量默认使用 `long long`。结果仍须在类型范围内；每个模板的适用条件和复杂度写在文件开头。
7. `.hpp` 是可复用组件，没有 `main()`。请运行自己的解答或 `examples/*.cpp`。

本地写法：

```cpp
#include <bits/stdc++.h>
#include "data_structures/fenwick.hpp"
using namespace std;

int main() {
    vector<long long> a{1, 2, 3};
    cp::Fenwick<long long> bit(a);
    bit.add(1, 5);
    cout << bit.sum(0, 3) << '\n'; // 11
}
```

任务已配置头文件搜索路径。**提交普通 OJ 前**运行 `CP: Export submission.cpp`，提交仓库根目录生成的 `submission.cpp`；导出会展开本地头文件及其依赖。也可以手动复制模板代码。不要把依赖本地 `.hpp` 的解答直接提交给不提供这些头文件的 OJ。

## 全部模板索引

### 基础与数据结构

| 模板 | 用途 / 复杂度 |
| --- | --- |
| [search.hpp](basic/search.hpp) | 二分第一个真值；有符号向上/下取整 |
| [compress.hpp](basic/compress.hpp) | 离散化，预处理 O(n log n)，查询 O(log n) |
| [dsu.hpp](data_structures/dsu.hpp) | 并查集，均摊 O(α(n)) |
| [fenwick.hpp](data_structures/fenwick.hpp) | 树状数组，O(log n)；第 k 小要求所有频次非负 |
| [segment_tree.hpp](data_structures/segment_tree.hpp) | 泛型线段树，O(log n)；结合律与单位元 |
| [lazy_segment_tree.hpp](data_structures/lazy_segment_tree.hpp) | 区间加、区间和，O(log n) |
| [sparse_table.hpp](data_structures/sparse_table.hpp) | ST 表，O(n log n) 建表，O(1) 查询；只用于幂等运算 |
| [xor_basis.hpp](data_structures/xor_basis.hpp) | 64 位异或线性基，允许空子集；第 k 小从 0 开始 |
| [binary_trie.hpp](data_structures/binary_trie.hpp) | 64 位 01 Trie，多重集合、最大异或，O(64) |

### 图与树

| 模板 | 用途 / 复杂度 |
| --- | --- |
| [shortest_path.hpp](graph/shortest_path.hpp) | BFS、01 BFS、Dijkstra、Floyd；Dijkstra 禁止负边 |
| [mst.hpp](graph/mst.hpp) | Kruskal 最小生成树/森林，O(m log m) |
| [topological_sort.hpp](graph/topological_sort.hpp) | 拓扑排序，O(n+m)；长度不足 n 表示有环 |
| [scc.hpp](graph/scc.hpp) | 强连通分量，迭代 Kosaraju，O(n+m)；编号按拓扑序 |
| [two_sat.hpp](graph/two_sat.hpp) | 2-SAT，O(n+m)，无解返回 `nullopt` |
| [lca.hpp](graph/lca.hpp) | 倍增 LCA / 距离 / 第 k 个祖先，查询 O(log n) |
| [tree_diameter.hpp](graph/tree_diameter.hpp) | 无权树直径路径，O(n) |
| [hld.hpp](graph/hld.hpp) | 迭代树链剖分，点权路径分成 O(log n) 段，子树连续 |
| [dinic.hpp](graph/dinic.hpp) | 最大流/最小割，一般图 O(V²E)；可建模二分图匹配 |

### 字符串

这些模板操作字节字符串，不把 UTF-8 汉字当成单个字符；Trie/AC 自动机只接受小写 `a-z`。

| 模板 | 用途 / 复杂度 |
| --- | --- |
| [kmp.hpp](string/kmp.hpp) | 前缀函数、所有匹配位置，O(n+m)，支持重叠与空模式 |
| [z_function.hpp](string/z_function.hpp) | Z 函数，O(n)，`z[0]=n` |
| [manacher.hpp](string/manacher.hpp) | 奇偶回文半径、最长回文区间，O(n) |
| [trie.hpp](string/trie.hpp) | 字典树、前缀计数、重复插入/删除，O(字符串长度) |
| [aho_corasick.hpp](string/aho_corasick.hpp) | AC 自动机、多模式出现次数；先插入再 build |
| [rolling_hash.hpp](string/rolling_hash.hpp) | 双模子串哈希，O(1) 查询；概率算法，有碰撞可能 |

### 数学、DP、几何与工具

| 模板 | 用途 |
| --- | --- |
| [number_theory.hpp](math/number_theory.hpp) | 安全模乘快速幂、一般模数逆元、线性筛、筛内质因数分解 |
| [modint.hpp](math/modint.hpp) | 静态模整数；`Mint=998244353`，`Mint1000000007` |
| [combinatorics.hpp](math/combinatorics.hpp) | 阶乘/逆阶乘、C(n,k)、A(n,k)；质数模数且 n < mod |
| [matrix.hpp](math/matrix.hpp) | 方阵乘法与快速幂，推荐配合 `ModInt` |
| [sequence.hpp](dp/sequence.hpp) | LIS/不下降子序列、严格逆序对、单调队列滑动最小值 |
| [knapsack.hpp](dp/knapsack.hpp) | 01 / 完全 / 多重背包；容量不超过 c 的最大价值 |
| [convex_hull.hpp](geometry/convex_hull.hpp) | 整数叉积、Andrew 凸包，去除中间共线点 |
| [debug.hpp](util/debug.hpp) | `debug(a, b)`，容器/pair/tuple 输出到 stderr；仅 LOCAL 启用 |
| [random.hpp](util/random.hpp) | 随机数据、打乱；支持固定种子重现对拍 |
| [hash.hpp](util/hash.hpp) | unordered_map 的随机盐哈希 |
| [graphviz.hpp](util/graphviz.hpp) | 保留原有图结构 DOT 输出工具，默认 0-based |

## 验证

VS Code：`Ctrl+Shift+P → Tasks: Run Task → CP: Test templates`。

`tests/algorithms.cpp` 使用固定随机种子，与朴素数组、枚举、BFS、最小割穷举等进行对拍；覆盖 64 位线性基、空容器、重复元素、图不连通等边界，并检查 20 万节点长链。

维护配置时，可额外运行 `python cp-stl/tests/test_tooling.py`（Python 3.10+）。它检查 35 个头文件的 GNU C++17 独立编译、中文/空格/特殊字符路径、原始字节输入、单文件导出、失败退出和 GDB 源码断点。日常运行不依赖 Python。
