# 模板性能检查与优化报告

检查范围为 `cp-stl` 的全部 35 个头文件：逐项审查时间/空间复杂度、重复计算、容器分配和深递归；对 16 种固定负载做新旧版本对照测量。大部分模板已采用常见的高效算法，本次优化集中在 5 个头文件，公开调用接口和已有示例输出保持一致。

## 测量方法

- 处理器：AMD Ryzen 7 8845HS；系统：Windows 11；编译器：MSYS2 UCRT64 GCC 15.2.0。
- 旧版：Git 提交 `c250d4f`。新版：本次优化后的源码；[原始记录](performance-results.json) 保存 35 个头文件和基准源文件的 SHA-256，换行统一为 LF 后计算。
- 相同基准程序、相同数据、固定种子 `20260919`。五轮交替运行旧版/新版，每个用例先预热一次，下面报告五次耗时的中位数。
- 编译参数：`-std=c++17 -O2 -DNDEBUG -Wall -Wextra -Wshadow`，不定义 `LOCAL`。数据生成、编译和终端输出不计时；表中注明的建树/建表包含在计时内。
- 新旧版本及各轮结果的校验和必须一致，否则脚本报错。完整正确性另由随机对拍、边界回归和示例输出验证。

这些数据用于比较本机上的具体负载，不能据此保证某道题的耗时或判断时间限制一定能通过。没有修改的模板也会因系统调度、缓存和分配器状态产生波动，不能把这些波动算作优化收益。

## 已实施的优化与实测

| 固定负载 | 旧版中位数 / ms | 新版中位数 / ms | 旧耗时 ÷ 新耗时 |
| --- | ---: | ---: | ---: |
| 线性基：秩 60，5 万次 kth | 79.90 | 7.60 | 10.51× |
| 模整数：1000 万次加法 | 26.02 | 6.52 | 3.99× |
| 模整数：10 万次随机快速幂 | 34.23 | 8.83 | 3.88× |
| 160 阶 uint64 矩阵：1 次幂，重复 8 次 | 27.02 | 14.58 | 1.85× |
| 40 阶模矩阵：10⁹ 次幂，重复 3 次 | 14.77 | 12.25 | 1.21× |
| 懒线段树：20 万元素、20 万次查询，含建树 | 54.88 | 38.00 | 1.44× |
| 懒线段树：20 万元素、20 万次操作，各半更新/查询，含建树 | 81.23 | 70.57 | 1.15× |
| 双模哈希：百万字节文本建表 | 10.90 | 9.63 | 1.13× |
| 双模哈希：百万字节文本、20 万次子串查询 | 10.23 | 3.84 | 2.66× |

1. **[线性基](../data_structures/xor_basis.hpp)**：以前每次 kth 都复制、消元并分配临时向量；现在按需缓存有序基，秩变化后首次有效查询 O(64²)，之后每次 O(64)。插入相关向量不会重建缓存。代价是缓存最多 64 个 uint64_t 的有效数据以及 vector 本身的开销；不调用 kth 时不分配缓存数组。
2. **[模整数](../math/modint.hpp)**：加法改为有界和的一次条件减模，并用无符号中间和覆盖接近 INT_MAX 的模数；静态 int 模数的幂直接使用 64 位乘法取模。通用 [pow_mod](../math/number_theory.hpp) 仍保留 __int128，继续支持大于 int 的模数。
3. **[矩阵](../math/matrix.hpp)**：处理完指数最后一位后停止平方。每次正指数调用少做一次 O(d³) 矩阵乘法；指数为 1 时收益明显，大指数时占比小。模矩阵这一行同时受益于模加法优化，不能全部归因于去掉末次平方。
4. **[懒线段树](../data_structures/lazy_segment_tree.hpp)**：不下传零标记，只递归进入与查询/修改区间相交的子树，减少无效函数调用。第一次仅跳过零标记时，混合负载曾略慢；表中记录的是进一步减少无效递归后的最终实现。
5. **[双模哈希](../string/rolling_hash.hpp)**：表内模值改用 uint32_t，乘法保持 64 位；查询归一化使用条件加模，减少一次取模。主要数组从 32(n+1) 字节降到 16(n+1) 字节，百万字节文本约 **30.52 MiB → 15.26 MiB**。这是按元素大小计算的数组有效数据，不是进程峰值内存；源串、容器和分配器开销另算。返回类型、模数、base 和哈希结果均不变。

## 未修改模板的规模参考

以下只列新版运行时的中位数，不把新旧波动解释为加速。图的建图过程在计时外；SCC 的内部反图和结果构造在计时内。随机用例不能代表所有极端图形。

| 固定负载 | 中位数 / ms |
| --- | ---: |
| 树状数组：20 万元素、20 万次操作，含建树 | 5.07 |
| 普通线段树：20 万元素、20 万次操作，含建树 | 11.09 |
| 并查集：20 万元素、20 万次合并与大小查询 | 2.63 |
| KMP：百万字符、长度 100 的模式、999901 个匹配 | 3.64 |
| AC：1 万个长度 12 的模式、百万字符文本，含建表 | 26.09 |
| Dijkstra：10 万点、30 万条有向边 | 29.22 |
| SCC：10 万点、30 万条有向边 | 44.73 |

## 全部 35 个模板的检查结论

下表额外空间不包含调用者已持有的输入，除非说明为输出/表存储。n 表示数组长度或点数，m 表示边数或模式长度，S 表示 Trie/AC 节点数，C 为背包容量，k 为物品数量，R 为二分范围。泛型组件默认比较和合并是 O(1)；若 T 是长字符串等类型，还要乘上实际操作成本。

### 基础与数据结构

| 模板 | 时间复杂度 | 额外空间 | 判断与使用建议 |
| --- | --- | --- | --- |
| [basic/search.hpp](../basic/search.hpp) | 二分 O(log R)，整除 O(1) | O(1) | 中点使用宽类型保障边界；真正耗时通常在判定函数。 |
| [basic/compress.hpp](../basic/compress.hpp) | 建表 O(n log n)，查询 O(log n) | O(n) | 排序去重合理；不再使用原数组时可移动传入，减少一次拷贝。 |
| [data_structures/dsu.hpp](../data_structures/dsu.hpp) | 初始化 O(n)，操作均摊 O(α(n)) | O(n) | 按大小合并、路径压缩已具备，保持现状。 |
| [data_structures/fenwick.hpp](../data_structures/fenwick.hpp) | 建树 O(n)，操作 O(log n) | O(n) | 单点加/区间和优先用它；数组紧凑，常数较小。 |
| [data_structures/segment_tree.hpp](../data_structures/segment_tree.hpp) | 建树 O(n)，修改/查询 O(log n) | O(n) | 迭代结构；保留泛型及非交换合并支持。 |
| [data_structures/lazy_segment_tree.hpp](../data_structures/lazy_segment_tree.hpp) | 建树 O(n)，操作 O(log n) | O(n) | 已减少零标记下传和无效递归；需要区间更新时使用。 |
| [data_structures/sparse_table.hpp](../data_structures/sparse_table.hpp) | 建表 O(n log n)，查询 O(1) | O(n log n) | 每层已只保存有效区间；查询快但大数组占内存。 |
| [data_structures/xor_basis.hpp](../data_structures/xor_basis.hpp) | 插入/普通查询 O(B)；首次 kth O(B²)，缓存后 O(B) | O(B)，B=64 | 已缓存消元结果；不调用 kth 不分配缓存数组。 |
| [data_structures/binary_trie.hpp](../data_structures/binary_trie.hpp) | 每次操作 O(B)，B=64 | 最坏 O(B·历史插入数) | 全 64 位数和大量不同值可能占用很大内存；删除不回收节点。 |

### 图与树

| 模板 | 时间复杂度 | 额外空间 | 判断与使用建议 |
| --- | --- | --- | --- |
| [graph/shortest_path.hpp](../graph/shortest_path.hpp) | BFS/01 BFS O(n+m)；堆 Dijkstra O((n+m) log(n+m))；Floyd O(n³) | BFS O(n)，堆最坏 O(n+m)；Floyd 原地 O(1)，距离矩阵 O(n²) | 按边权和规模选算法；稀疏图不要默认开 n² 矩阵。 |
| [graph/mst.hpp](../graph/mst.hpp) | O(m log m) | O(n+m) | 排序主导；边列表按值传入会复制，可在原数据不再使用时移动传参。 |
| [graph/topological_sort.hpp](../graph/topological_sort.hpp) | O(n+m) | O(n) | Kahn 算法合理，返回顺序同时充当队列。 |
| [graph/scc.hpp](../graph/scc.hpp) | O(n+m) | O(n+m) | 迭代遍历可处理深链；反图、分组及小块分配是主要内存成本。 |
| [graph/two_sat.hpp](../graph/two_sat.hpp) | O(变量数+子句数) | O(变量数+子句数) | 复用 SCC，规模大时先估算蕴含图和反图内存。 |
| [graph/lca.hpp](../graph/lca.hpp) | 预处理 O(n log n)，查询 O(log n) | O(n log n) | 倍增层数动态计算、迭代遍历；已经过 20 万节点链测试。 |
| [graph/tree_diameter.hpp](../graph/tree_diameter.hpp) | O(n) | O(n) | 两次 BFS 适合无权树；返回路径和临时父数组占线性空间。 |
| [graph/hld.hpp](../graph/hld.hpp) | 预处理 O(n)，路径拆分 O(log n) | O(n)，不含区间结构 | 接 O(log n) 线段树后，路径操作是 O(log² n)。 |
| [graph/dinic.hpp](../graph/dinic.hpp) | 一般网络 O(V²E) | O(V+E)，另有 O(V) 递归栈 | 有当前弧优化；深网络仍有栈溢出风险，大网络需按结构选择实现。 |

### 字符串

| 模板 | 时间复杂度 | 额外空间 | 判断与使用建议 |
| --- | --- | --- | --- |
| [string/kmp.hpp](../string/kmp.hpp) | O(n+m)，含输出 | O(m+匹配数) | 线性算法；大量匹配时存放输出位置本身也要时间和空间。 |
| [string/z_function.hpp](../string/z_function.hpp) | O(n) | O(n) | 线性算法，保持现状。 |
| [string/manacher.hpp](../string/manacher.hpp) | O(n) | O(n) | 奇偶半径共两张 int 数组，无须为速度另换算法。 |
| [string/trie.hpp](../string/trie.hpp) | 单次 O(字符串长度) | O(26S) | 常见平台每节点约 112 字节；删除不回收，关注历史节点总数 S。 |
| [string/aho_corasick.hpp](../string/aho_corasick.hpp) | 建表 O(26S)，统计 O(文本长度+S+模式数) | O(26S+模式数) | 每次 count 都遍历 fail 序；很多短文本查询大自动机时，这部分可能主导。 |
| [string/rolling_hash.hpp](../string/rolling_hash.hpp) | 预处理 O(n)，查询 O(1) | 主要数组 16(n+1) 字节 | 已压缩模值存储、减少查询取模；概率算法，仍有碰撞可能。 |

### 数学、DP、几何

| 模板 | 时间复杂度 | 额外空间 | 判断与使用建议 |
| --- | --- | --- | --- |
| [math/number_theory.hpp](../math/number_theory.hpp) | 模幂/逆元 O(log 参数)，筛 O(n)，分解 O(log x) | 筛 O(n)，分解结果 O(log x)，标量运算 O(1) | 通用 64 位模数保留 __int128 中间乘积，避免以溢出换速度。 |
| [math/modint.hpp](../math/modint.hpp) | 加减乘 O(1)，幂/逆元 O(log 参数) | 每个对象 O(1) | 已减少加法取模，并让静态 int 模数的幂使用 64 位乘积。 |
| [math/combinatorics.hpp](../math/combinatorics.hpp) | 预处理 O(N+log p)，单次查询 O(1) | O(N) | 同一模数/上界预处理一次后复用，不要每次查询重新建表。 |
| [math/matrix.hpp](../math/matrix.hpp) | 乘法 O(d³)，快速幂 O(d³ log e) | O(d²) | 已去掉最后一次无用平方；循环原本就是 i-k-j，大维度瓶颈仍是立方复杂度。 |
| [dp/sequence.hpp](../dp/sequence.hpp) | LIS/逆序对 O(n log n)，滑动最小值 O(n) | O(n) | 渐进复杂度合理；有性能证据时再比较归并计数和当前离散化+Fenwick。 |
| [dp/knapsack.hpp](../dp/knapsack.hpp) | 单物品 01/完全 O(C)，多重 O(C log(k+1)) | O(C) | 容量 C 和数量 k 大时，算法选型比循环微调更重要。 |
| [geometry/convex_hull.hpp](../geometry/convex_hull.hpp) | O(n log n) | O(n) | 排序主导；保留精确叉积，不改成浮点数。 |

### 辅助工具

| 模板 | 时间复杂度 | 额外空间 | 判断与使用建议 |
| --- | --- | --- | --- |
| [util/debug.hpp](../util/debug.hpp) | 与展开并打印的内容量成正比 | 取决于嵌套深度和流缓冲 | LOCAL 下频繁输出很慢；性能测量不要在热循环打印容器。 |
| [util/random.hpp](../util/random.hpp) | 单个整数平均 O(1)，数组/打乱 O(n) | 生成器 O(1)，返回数组 O(n) | 复用生成器；基准数据生成放在计时区间外。 |
| [util/hash.hpp](../util/hash.hpp) | 容器操作平均 O(1)，最坏仍可能退化 | 取决于哈希容器规模 | 可预设 reserve 和负载因子；随机盐不能保证最坏 O(1)。 |
| [util/graphviz.hpp](../util/graphviz.hpp) | O(点数+边数+输出字符数) | to_dot 额外保存全部文本 | 调试工具；很大图可用 dump_graph 写流，避免额外保存整个字符串。 |

## 仍有优化空间，但应结合题目选择

- **只有单点加和区间和**：优先 Fenwick。`RangeAddSum` 的两张 long long 数组大约占 64n 字节，Fenwick<long long> 的树数组约占 8(n+1) 字节；没有区间更新需求时，不必承担懒标记的时间和空间。
- **大量 64 位异或数据**：BinaryTrie 每节点通常为 12 字节，节点数最坏为 1+64×历史插入数；vector 容量扩张还可能增加常驻和峰值内存。只有在插入值和查询值的位宽都已确定时，才考虑专门裁剪位宽，不能直接把通用模板的 64 改成 30。
- **大字典、多次短文本查询**：Trie/AC 的 26 路数组占内存；当前 AC 每次 count 都分配计数数组并沿 fail 序传播。可根据字符集或查询方式设计稀疏转移/其他计数方式，但可能增加查询常数或改变接口。
- **非常深或非常大的流网络**：Dinic 的 DFS 仍然递归；20 万节点树的测试不代表 20 万层流网络也安全。需要这类图时，应选择迭代增广或适合具体网络结构的实现。
- **大量边的图**：目前邻接表使用 vector<vector<...>>，可在构图前统计出度并 reserve；更紧的内存限制下再考虑连续边表。Kruskal 提前连通后停止扫描、逆序对改为归并计数等也是候选方向，需要对目标数据测量，当前未宣称有实测收益。
- **容量很大的多重背包**：本模板二进制拆分为 O(C log(k+1))；按重量余数分组并用单调队列可做到单物品 O(C)，但实现更复杂。大维度矩阵仍是 O(d³)，应先利用递推或转移结构减少维度。

## 正确性和使用流程回归

- 随机对拍及 20 万节点长链测试通过。
- 补充线性基插入与查询交错、缓存复制与满秩 64；模 2、复合模数、常用模数和 INT_MAX 附近模数的加法/幂；哈希的 NUL/高位字节及独立多项式校验；懒标记正负抵消测试。
- 全部 38 个示例的 GNU C++17 编译、标准输出与标准错误检查通过；关闭 LOCAL 的 debug 示例也通过。
- 35 个头文件独立编译、中文/特殊字符路径、原始字节输入、单文件导出和 GDB 源码断点由 tooling 测试验证。

## 自己复测

在仓库根目录执行，需 Python 3.10+ 和配置好的 GCC：

```powershell
python cp-stl/tests/benchmark.py --baseline c250d4f --repeats 5
```

不传 `--baseline` 只测当前版本；可用 `--compiler` 指定编译器。脚本从 Git 提取旧头文件到忽略目录 `.build/benchmarks`，不会切换分支或改动当前源码。全部原始耗时写入 `.build/benchmarks/results.json`；本报告对应的快照是 [performance-results.json](performance-results.json)。

为减小波动，测试期间保持相同电源模式，并避免同时运行编译、游戏等重负载。日常 `F5` 使用调试编译参数，不能直接将它的耗时与这里的 `-O2 -DNDEBUG` 测量比较。

[模板首页](../README.md) · [逐个模板的使用手册](usage/README.md) · [基准程序](../tests/benchmarks.cpp) · [运行脚本](../tests/benchmark.py)
