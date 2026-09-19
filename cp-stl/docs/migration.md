# 整理记录

整理基于提交 `7d68060b0c5e731719bafe66fd180e8b84742e7b`。开始时工作区没有 Git 报告的未提交改动。旧 `lsl-cp-template` 有 571 个文件，旧 `cp-stl` 有 7 个文件；`other-oj` 有 6 个文件。

## 整理原则与去向

| 旧内容 | 现在的入口 / 处理 |
| --- | --- |
| 多套起手式、预编译头、重复调试打印 | [template.cpp](../template.cpp) 和 [util/debug.hpp](../util/debug.hpp)，统一 GNU C++17+ |
| `cp-stl/sparse_table.cppm`、`ops.cppm` | [sparse_table.hpp](../data_structures/sparse_table.hpp)，移除模块构建要求，处理空数组 |
| `cp-stl/random_utils.cppm`、随机数据构造 | [random.hpp](../util/random.hpp)，支持固定种子 |
| `cp-stl/tree_distance.cpp`、树上倍增 | [lca.hpp](../graph/lca.hpp)，动态计算倍增层数，迭代建树 |
| `cp-stl/tree_diameter.cpp` | [tree_diameter.hpp](../graph/tree_diameter.hpp)，保留直径点序列接口思路 |
| `cp-stl/xor_base.cpp` | [xor_basis.hpp](../data_structures/xor_basis.hpp)，支持完整 64 位，修正边界与错误值表示 |
| 未完成的 `cp-stl/segtree.cpp`、多套线段树 | [segment_tree.hpp](../data_structures/segment_tree.hpp) / [lazy_segment_tree.hpp](../data_structures/lazy_segment_tree.hpp) |
| 多套并查集、树状数组、ST、Trie | 每类保留一套：见 [索引](../README.md) |
| 旧图论、字符串、数学、背包模板 | 按统一下标、区间和命名整理/重写，并增加独立编译和随机对拍 |
| `graphviz_debug.hpp` | [util/graphviz.hpp](../util/graphviz.hpp)，保留原实现，默认下标改为 0 |
| `code-library` 第三方全集、重复注释版、题目特化代码、空占位、PDF/DOCX | 清理；进阶常用组件链接到已有 ACL，历史内容仍可从 Git 查看 |
| `other-oj` | 按要求删除整个目录及其中 6 个文件 |

统一后的模板、说明、示例、运行脚本和测试都在 `cp-stl`。VS Code 需要从仓库根目录读取共享 `.vscode` 配置。

## 接口变化要留意

- 树的编号由旧版常见的 **1-based 改为 0-based**。
- ST 等区间由部分旧版本的闭区间改为统一的 **[l,r)**。
- 线性基 `kth(k)` 是 **0-based、去重、允许空子集**；无解返回 `std::nullopt`，不再用最大无符号数兼任错误码。0 永远可表示。
- 随机哈希和字符串哈希不承诺“绝不可能被 hack / 绝无碰撞”。
- 单文件题解不再混在算法头文件里。`examples` 是可运行示例，`tests` 是验证代码。
- 新调试打印仅在 `LOCAL` 下启用，任务自动定义 LOCAL；OJ 提交不需要额外的本地调试头文件。

## 如何查看少用的旧内容

没有另建一个同样混乱的 archive 目录。确有需要时用 Git 查看整理前的文件：

```powershell
git ls-tree -r --name-only 7d68060b0c5e731719bafe66fd180e8b84742e7b -- lsl-cp-template
git show "7d68060b0c5e731719bafe66fd180e8b84742e7b:lsl-cp-template/图论/HLD.cpp"
```

旧代码未因此变成已验证组件；若将某个进阶算法重新加入常用库，应补全使用条件和针对性验证。
