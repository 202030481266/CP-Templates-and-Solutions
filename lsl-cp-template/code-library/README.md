# 算法模板术语对照表

本文档提供 `lsl-cp-template/code-library` 中所有算法模板的**英文名称 ↔ 中文名称**对照，帮助你快速定位所需算法。

---

## 📋 目录

- [算法模板术语对照表](#算法模板术语对照表)
  - [📋 目录](#-目录)
  - [一、数据结构 (Data Structures)](#一数据结构-data-structures)
  - [二、图论 (Graph Theory)](#二图论-graph-theory)
  - [二、图论 (Graph Theory)](#二图论-graph-theory-1)
  - [三、数学 (Math)](#三数学-math)
  - [四、数论 (Number Theory)](#四数论-number-theory)
  - [五、字符串 (Strings)](#五字符串-strings)
  - [六、动态规划优化 (Dynamic Programming Optimizations)](#六动态规划优化-dynamic-programming-optimizations)
  - [七、计算几何 (Geometry)](#七计算几何-geometry)
  - [八、博弈论 (Game Theory)](#八博弈论-game-theory)
  - [九、杂项 (Miscellaneous)](#九杂项-miscellaneous)
  - [📊 统计信息](#-统计信息)
  - [🔍 快速查找指南](#-快速查找指南)
    - [按中文关键词查找](#按中文关键词查找)

---

## 一、数据结构 (Data Structures)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 增强并查集 | Augmented DSU | `Data Structures/Augmented DSU.cpp` |
| 平衡括号树 | Balanced Bracket Tree | `Data Structures/Balanced Bracket Tree.cpp` |
| 树状数组 | BIT | `Data Structures/BIT.cpp` |
| 二维树状数组(区间更新+区间查询) | BIT 2D with Range Update and Range Query | `Data Structures/BIT 2D with Range Update and Range Query.cpp` |
| 树状数组(区间更新+区间查询) | BIT with Range Update and Range Query | `Data Structures/BIT with Range Update and Range Query.cpp` |
| 二叉搜索树(STL实现) | BST using STL | `Data Structures/BST using STL.cpp` |
| 二叉化树 | Binarizing a Tree | `Data Structures/Binarizing a Tree.cpp` |
| 笛卡尔树 | Cartesian Tree | `Data Structures/Cartesian Tree.cpp` |
| 点分治 | Centroid Decomposition | `Data Structures/Centroid Decomposition.cpp` |
| 可持久化点分治 | Centroid Decomposition Persistent | `Data Structures/Centroid Decomposition Persistent.cpp` |
| 并查集 | DSU | `Data Structures/DSU.cpp` |
| 树上并查集 | DSU on Tree | `Data Structures/DSU on Tree.cpp` |
| 部分可持久化并查集 | DSU Partially Persistent | `Data Structures/DSU Partially Persistent.cpp` |
| 可回滚并查集 | DSU with Rollbacks | `Data Structures/DSU with Rollbacks.cpp` |
| 不相交稀疏表 | Disjoint Sparse Table | `Data Structures/Disjoint Sparse Table.cpp` |
| 插入查询问题的分治法 | Divide and Conquer for Insert and Query Problems | `Data Structures/Divide and Conquer for Insert and Query Problems.cpp` |
| 动态连通性问题 | Dynamic Connectivity Problem | `Data Structures/Dynamic Connectivity Problem.cpp` |
| 在线动态直径 | Dynamic Diameter Online | `Data Structures/Dynamic Diameter Online.cpp` |
| 轻重链剖分 | HLD | `Data Structures/HLD.cpp` |
| 可持久化懒标记链剖 | HLD with Persistent Lazy Propagation | `Data Structures/HLD with Persistent Lazy Propagation.cpp` |
| 隐式Treap | Implicit Treap | `Data Structures/Implicit Treap.cpp` |
| 区间集合 | Interval Set | `Data Structures/Interval Set.cpp` |
| KD树 | KD Tree | `Data Structures/KD Tree.cpp` |
| 最近公共祖先 | LCA | `Data Structures/LCA.cpp` |
| 动态树 | Link Cut Tree | `Data Structures/Link Cut Tree.cpp` |
| 莫队算法 | MOs Algorithm | `Data Structures/MOs Algorithm.cpp` |
| 树上莫队 | MOs on tree | `Data Structures/MOs on tree.cpp` |
| 在线莫队 | MOs Online | `Data Structures/MOs Online.cpp` |
| 带并查集的莫队 | MOs with DSU | `Data Structures/MOs with DSU.cpp` |
| 带修改的莫队 | MOs with Update | `Data Structures/MOs with Update.cpp` |
| 单调队列 | Monotonous Queue | `Data Structures/Monotonous Queue.cpp` |
| 莫队套莫队 | Mos within Mos | `Data Structures/Mos within Mos.cpp` |
| 有序集合 | Ordered Set | `Data Structures/Ordered Set.cpp` |
| 排列树 | Permutation Tree | `Data Structures/Permutation Tree.cpp` |
| 可持久化数组 | Persistent Array | `Data Structures/Persistent Array.cpp` |
| 可持久化可并堆 | Persistent Meldable Heap | `Data Structures/Persistent Meldable Heap.cpp` |
| 可持久化队列 | Persistent Queue | `Data Structures/Persistent Queue.cpp` |
| 可持久化字典树 | Persistent Trie | `Data Structures/Persistent Trie.cpp` |
| 可持久化并查集 | Persistent UnionFind | `Data Structures/Persistent UnionFind.cpp` |
| 队列撤销技巧 | Queue Undo Trick | `Data Structures/Queue Undo Trick.cpp` |
| 可达性树 | Reachability Tree | `Data Structures/Reachability Tree.cpp` |
| 线段树 | Segment Tree | `Data Structures/Segment Tree.cpp` |
| 动态二维线段树 | Segment Tree 2D Dynamic | `Data Structures/Segment Tree 2D Dynamic.cpp` |
| 线段树Beats | Segment Tree Beats | `Data Structures/Segment Tree Beats.cpp` |
| 懒标记线段树 | Segment Tree Lazy | `Data Structures/Segment Tree Lazy.cpp` |
| 线段树合并 | Segment Tree Merging | `Data Structures/Segment Tree Merging.cpp` |
| 非递归线段树 | Segment Tree NonRecursive | `Data Structures/Segment Tree NonRecursive.cpp` |
| 可持久化线段树 | Segment Tree Persistent | `Data Structures/Segment Tree Persistent.cpp` |
| 可持久化懒标记线段树 | Segment Tree Persistent Lazy | `Data Structures/Segment Tree Persistent Lazy.cpp` |
| 等差数列线段树 | Segment Tree with Arithmetic Progression | `Data Structures/Segment Tree with Arithmetic Progression.cpp` |
| 稀疏表 | Sparse Table | `Data Structures/Sparse Table.cpp` |
| 二维稀疏表 | Sparse Table 2D | `Data Structures/Sparse Table 2D.cpp` |
| 平方根树 | SQRT Tree | `Data Structures/SQRT Tree.cpp` |
| 带逆更新的分块 | Square Root Decomposition With Reverse Update | `Data Structures/Square Root Decomposition With Reverse Update.cpp` |
| 静态转动态技巧 | Static to Dynamic Trick | `Data Structures/Static to Dynamic Trick.cpp` |
| Top树 | Top Tree | `Data Structures/Top Tree.cpp` |
| Treap树堆 | Treap | `Data Structures/Treap.cpp` |
| 可持久化Treap | Treap persistent | `Data Structures/Treap persistent.cpp` |
| 字典树 | Trie | `Data Structures/Trie.cpp` |
| 威尼斯技巧 | Venice Technique | `Data Structures/Venice Technique.cpp` |
| 小波树 | Wavelet Tree | `Data Structures/Wavelet Tree.cpp` |
| 异或线段树 | XOR Segment Tree | `Data Structures/XOR Segment Tree.cpp` |

---

## 二、图论 (Graph Theory)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 2-可满足性问题 | 2 SAT | `Graph Theory/2 SAT.cpp` |
| 3环和4环 | 3 CYCLE and 4 CYCLE | `Graph Theory/3 CYCLE and 4 CYCLE.cpp` |
| 3-可满足性问题 | 3 SAT | `Graph Theory/3 SAT.cpp` |
| 割边 | Articulation Bridges | `Graph Theory/Articulation Bridges.cpp` |
| 割点 | Articulation Points | `Graph Theory/Articulation Points.cpp` |
| 贝尔曼-福特算法 | Bellman Ford | `Graph Theory/Bellman Ford.cpp` |
| 块割树 | Block Cut Tree | `Graph Theory/Block Cut Tree.cpp` |
| 带花树算法(一般图匹配) | Blossom Algorithm | `Graph Theory/Blossom Algorithm.cpp` |
| 带权带花树算法 | Blossom Algorithm Weighted | `Graph Theory/Blossom Algorithm Weighted.cpp` |
| Boruvka最小生成树算法 | Boruvka's Algorithm | `Graph Theory/Boruvka's Algorithm.cpp` |
| 仙人掌图 | Cactus Graph | `Graph Theory/Cactus Graph.cpp` |
| 中国邮路问题 | Chinese Postman Problem | `Graph Theory/Chinese Postman Problem.cpp` |
| 弦图 | Chordal Graph | `Graph Theory/Chordal Graph.cpp` |
| 色数 | Chromatic Number | `Graph Theory/Chromatic Number.cpp` |
| 色多项式 | Chromatic Polynoimial | `Graph Theory/Chromatic Polynoimial.cpp` |
| 标记图计数 | Counting Labeled Graphs | `Graph Theory/Counting Labeled Graphs.cpp` |
| 环检测 | Cycle Detection | `Graph Theory/Cycle Detection.cpp` |
| 动态DAG可达性 | DAG Reachability Dynamic | `Graph Theory/DAG Reachability Dynamic.cpp` |
| 迪杰斯特拉算法 | Dijkstra | `Graph Theory/Dijkstra.cpp` |
| 线段树上的Dijkstra | Dijkstra on Segment Tree | `Graph Theory/Dijkstra on Segment Tree.cpp` |
| Dinic最大流算法 | Dinics Algorithm | `Graph Theory/Dinics Algorithm.cpp` |
| 有向最小生成树 | Directed MST | `Graph Theory/Directed MST.cpp` |
| 支配树 | Dominator Tree | `Graph Theory/Dominator Tree.cpp` |
| 动态最小生成树 | Dynamic MST | `Graph Theory/Dynamic MST.cpp` |
| 二分图边着色 | Edge Coloring Bipartite Graph | `Graph Theory/Edge Coloring Bipartite Graph.cpp` |
| 快速二分图边着色 | Edge Coloring Bipartite Graph Faster | `Graph Theory/Edge Coloring Bipartite Graph Faster.cpp` |
| 简单图边着色 | Edge Coloring Simple Graph | `Graph Theory/Edge Coloring Simple Graph.cpp` |
| Eppstein算法(k短路) | Eppsteins Algorithm | `Graph Theory/Eppsteins Algorithm.cpp` |
| 有向欧拉路径 | Euler Path Directed | `Graph Theory/Euler Path Directed.cpp` |
| 无向欧拉路径 | Euler Path Undirected | `Graph Theory/Euler Path Undirected.cpp` |
| 弗洛伊德算法 | Floyd Warshall | `Graph Theory/Floyd Warshall.cpp` |
| Gomory-Hu树 | Gomory Hu Tree | `Graph Theory/Gomory Hu Tree.cpp` |
| 平面图的Gomory-Hu树 | Gomory Hu Tree of Planar Graph | `Graph Theory/Gomory Hu Tree of Planar Graph.cpp` |
| 矩阵的Hafnian | Hafnian of a Matrix | `Graph Theory/Hafnian of a Matrix.cpp` |
| Hopcroft-Karp二分图匹配 | HopCroft Karp Algorithm | `Graph Theory/HopCroft Karp Algorithm.cpp` |
| 匈牙利算法 | Hungarian Algorithm | `Graph Theory/Hungarian Algorithm.cpp` |
| 补图 | Inverse Graph | `Graph Theory/Inverse Graph.cpp` |
| Johnson全源最短路 | Johnson's Algorithm | `Graph Theory/Johnson's Algorithm.cpp` |
| 基尔霍夫定理(矩阵树定理) | Kirchoffs Theorem | `Graph Theory/Kirchoffs Theorem.cpp` |
| Kruskal最小生成树 | Krushkal's MST | `Graph Theory/Krushkal's MST.cpp` |
| Kuhn算法 | Kuhns Algorithm | `Graph Theory/Kuhns Algorithm.cpp` |
| Dinic算法的上下界网络流 | L R Flow with Dinic | `Graph Theory/L R Flow with Dinic.cpp` |
| 最小费用最大流的上下界网络流 | L R Flow with MCMF | `Graph Theory/L R Flow with MCMF.cpp` |
| 最近公共祖先 | LCA | `Graph Theory/LCA.cpp` |
| O(1) LCA | LCA in O(1) | `Graph Theory/LCA in O(1).cpp` |
| 长路径剖分 | Long Path Decomposition | `Graph Theory/Long Path Decomposition.cpp` |
| 曼哈顿最小生成树 | Manhattan MST | `Graph Theory/Manhattan MST.cpp` |
| 最大团 | Maximum Clique | `Graph Theory/Maximum Clique.cpp` |
| 快速最大团和最大独立集 | Maximum Clique and MIS Super Fast | `Graph Theory/Maximum Clique and MIS Super Fast.cpp` |
| 最大权闭合子图 | Maximum Closure Problem | `Graph Theory/Maximum Closure Problem.cpp` |
| 最大密度子图 | Maximum Density Subgraph | `Graph Theory/Maximum Density Subgraph.cpp` |
| 最大独立集 | Maximum Independant Set | `Graph Theory/Maximum Independant Set.cpp` |
| 最小费用最大流 | Min Cost Max Flow | `Graph Theory/Min Cost Max Flow.cpp` |
| 带负环的最小费用最大流 | Min Cost Max Flow with Negative Cycles | `Graph Theory/Min Cost Max Flow with Negative Cycles.cpp` |
| 平面图最小割 | Min Cut in a Planar Graph | `Graph Theory/Min Cut in a Planar Graph.cpp` |
| 一般图最小费用顶点覆盖 | Minimum Cost Vertex Cover General Graph | `Graph Theory/Minimum Cost Vertex Cover General Graph.cpp` |
| 最小直径生成树 | Minimum Diameter Spanning Tree | `Graph Theory/Minimum Diameter Spanning Tree.cpp` |
| 最小平均权环 | Minimum Mean Weight Cycle | `Graph Theory/Minimum Mean Weight Cycle.cpp` |
| 每条边的最小权环 | Minimum Weight Cycle For Each Edge | `Graph Theory/Minimum Weight Cycle For Each Edge.cpp` |
| 每个顶点的最小权环 | Minimum Weight Cycle For Each Vertex | `Graph Theory/Minimum Weight Cycle For Each Vertex.cpp` |
| 生成树数目 | Number of Arborescence | `Graph Theory/Number of Arborescence.cpp` |
| DAG数目 | Number of DAG | `Graph Theory/Number of DAG.cpp` |
| 不同团的数目 | Number of Different Cliques | `Graph Theory/Number of Different Cliques.cpp` |
| 树中各长度路径数目 | Number of Paths of Each Length in a Tree | `Graph Theory/Number of Paths of Each Length in a Tree.cpp` |
| 在线割边 | Online Articulation Bridges | `Graph Theory/Online Articulation Bridges.cpp` |
| 路径交 | Path Intersection | `Graph Theory/Path Intersection.cpp` |
| 路径并 | Path Union | `Graph Theory/Path Union.cpp` |
| Prim最小生成树 | Prim's MST | `Graph Theory/Prim's MST.cpp` |
| Prufer序列 | Prufer Code | `Graph Theory/Prufer Code.cpp` |
| 随机化无权匹配 | Randomized Matching Unweighted | `Graph Theory/Randomized Matching Unweighted.cpp` |
| 随机化带权匹配 | Randomized Matching Weighted | `Graph Theory/Randomized Matching Weighted.cpp` |
| 强连通分量 | SCC | `Graph Theory/SCC.cpp` |
| 最短路径快速算法 | SPFA | `Graph Theory/SPFA.cpp` |
| 不经过每条边的最短路 | Shortest Path That Doesnt Pass Through Each Edge | `Graph Theory/Shortest Path That Doesnt Pass Through Each Edge.cpp` |
| ST编号 | ST Numbering | `Graph Theory/ST Numbering.cpp` |
| 稳定婚姻问题 | Stable Marriage Problem | `Graph Theory/Stable Marriage Problem.cpp` |
| 斯坦纳树问题 | Steiner Tree Problem | `Graph Theory/Steiner Tree Problem.cpp` |
| Stoer-Wagner全局最小割 | Stoer Wagner Algorithm | `Graph Theory/Stoer Wagner Algorithm.cpp` |
| 差分约束系统 | System Of Difference Constraints | `Graph Theory/System Of Difference Constraints.cpp` |
| 三边连通性 | Three Edge Connectivity | `Graph Theory/Three Edge Connectivity.cpp` |
| 树同构 | Tree Isomorphism | `Graph Theory/Tree Isomorphism.cpp` |
| 树定向 | Tree Orientation | `Graph Theory/Tree Orientation.cpp` |
| Tutte定理 | Tuttes Theorem | `Graph Theory/Tuttes Theorem.cpp` |
| 唯一最小割 | Unique Min Cut | `Graph Theory/Unique Min Cut.cpp` |
| 虚树 | Virtual Tree | `Graph Theory/Virtual Tree.cpp` |

---

## 二、图论 (Graph Theory)

> 注：图论部分已在数据结构中展示，实际文件位于 `Graph Theory/` 目录下。

---

## 三、数学 (Math)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 所有完美匹配的异或值 | All Possible Perfect Matching XOR Values | `Math/All Possible Perfect Matching XOR Values.cpp` |
| 线性基 | Basis Vector | `Math/Basis Vector.cpp` |
| 约化行阶梯形式线性基 | Basis Vector Reduced Row Echelon Form | `Math/Basis Vector Reduced Row Echelon Form.cpp` |
| 带权线性无关向量的线性基 | Basis Vector ft Weighted Linearly Independent Vectors | `Math/Basis Vector ft Weighted Linearly Independent Vectors.cpp` |
| Berlekamp-Massey算法 | BerleKamp Massey | `Math/BerleKamp Massey.cpp` |
| 快速特征多项式 | Characteristic Polynomial Faster | `Math/Characteristic Polynomial Faster.cpp` |
| 循环卷积 | Cyclic Convolution | `Math/Cyclic Convolution.cpp` |
| 行列式 | Determinant | `Math/Determinant.cpp` |
| 循环矩阵的行列式 | Determinant of Cyclic Matrix | `Math/Determinant of Cyclic Matrix.cpp` |
| 置换矩阵的行列式 | Determinant of Permutant Matrix | `Math/Determinant of Permutant Matrix.cpp` |
| 乘积矩阵的行列式 | Determinant of Product Matrix | `Math/Determinant of Product Matrix.cpp` |
| 稀疏矩阵的行列式 | Determinant of Sparse Matrix | `Math/Determinant of Sparse Matrix.cpp` |
| 合数模下的行列式 | Determinant under Composite Modulo | `Math/Determinant under Composite Modulo.cpp` |
| 质数模下的行列式 | Determinant under Prime Modulo | `Math/Determinant under Prime Modulo.cpp` |
| 快速Faulhaber公式 | Faulhaber Formula Fastest | `Math/Faulhaber Formula Fastest.cpp` |
| 快速傅里叶变换 | FFT | `Math/FFT.cpp` |
| 快速沃尔什-哈达玛变换 | FWHT | `Math/FWHT.cpp` |
| 任意基的FWHT | FWHT in Any Base | `Math/FWHT in Any Base.cpp` |
| 三进制基的FWHT | FWHT in Ternary Base | `Math/FWHT in Ternary Base.cpp` |
| 二进制有限域运算 | Finite Field Arithmetic Binary | `Math/Finite Field Arithmetic Binary.cpp` |
| Freivalds算法 | Freivalds Algorithm | `Math/Freivalds Algorithm.cpp` |
| 高斯消元 | Gaussian Elimination | `Math/Gaussian Elimination.cpp` |
| 模高斯消元 | Gaussian Elimination Modular | `Math/Gaussian Elimination Modular.cpp` |
| 模2高斯消元 | Gaussian Elimination Modulo 2 | `Math/Gaussian Elimination Modulo 2.cpp` |
| 线性递推的生成函数 | Generating Function of a Linear Recurrence | `Math/Generating Function of a Linear Recurrence.cpp` |
| 矩阵的Hafnian | Hafnian of a Matrix | `Math/Hafnian of a Matrix.cpp` |
| Romberg积分 | Integration (Romberg) | `Math/Integration (Romberg).cpp` |
| Simpson积分 | Integration (Simpsons) | `Math/Integration (Simpsons).cpp` |
| 矩阵求逆 | Inverse of A Matrix | `Math/Inverse of A Matrix.cpp` |
| 模2矩阵求逆 | Inverse of A Matrix modulo 2 | `Math/Inverse of A Matrix modulo 2.cpp` |
| 拉格朗日插值 | Lagrange Interpolation | `Math/Lagrange Interpolation.cpp` |
| 暴力拉格朗日插值 | Lagrange Interpolation Brute | `Math/Lagrange Interpolation Brute.cpp` |
| 带多项式提取的拉格朗日插值 | Lagrange Interpolation with Polynomial Extraction | `Math/Lagrange Interpolation with Polynomial Extraction.cpp` |
| 拉格朗日乘数法 | Lagrange Multiplier | `Math/Lagrange Multiplier.cpp` |
| 线性递推 | Linear Recurrence | `Math/Linear Recurrence.cpp` |
| 快速线性递推 | Linear Recurrence Fastest | `Math/Linear Recurrence Fastest.cpp` |
| 多项式系数线性递推 | Linear Recurrence With Polynomial Coefficients | `Math/Linear Recurrence With Polynomial Coefficients.cpp` |
| 矩阵快速幂 | Matrix Exponentiation | `Math/Matrix Exponentiation.cpp` |
| 多项式系数矩阵快速幂 | Matrix Exponentiation With Polynomial Coefficients | `Math/Matrix Exponentiation With Polynomial Coefficients.cpp` |
| 凸函数间的最大卷积 | Max Convolution between Convex Funtions | `Math/Max Convolution between Convex Funtions.cpp` |
| 快速数论变换 | NTT | `Math/NTT.cpp` |
| 二维NTT | NTT 2D | `Math/NTT 2D.cpp` |
| 在线NTT | NTT Online | `Math/NTT Online.cpp` |
| 分治在线NTT | NTT Online (D&C) | `Math/NTT Online (D&C).cpp` |
| 任意素数模的NTT | NTT With Any Prime MOD | `Math/NTT With Any Prime MOD.cpp` |
| 方程解的数量(中途相遇) | Number of Solutions of A Equation MITM | `Math/Number of Solutions of A Equation MITM.cpp` |
| 矩阵的积和式 | Permanent of a Matrix | `Math/Permanent of a Matrix.cpp` |
| 多项式 | Polynomial | `Math/Polynomial.cpp` |
| 多项式因式分解 | Polynomial Factorization | `Math/Polynomial Factorization.cpp` |
| 多项式求和 | Polynomial Sum | `Math/Polynomial Sum.cpp` |
| 带二项式系数的多项式 | Polynomial with Binomial Coefficients | `Math/Polynomial with Binomial Coefficients.cpp` |
| Reeds-Sloane算法 | Reeds Sloane Algorithm | `Math/Reeds Sloane Algorithm.cpp` |
| 单纯形法 | Simplex Algorithm | `Math/Simplex Algorithm.cpp` |
| 子集和问题 | Subset Sum Problem | `Math/Subset Sum Problem.cpp` |
| Slime技巧 | The Slime Trick | `Math/The Slime Trick.cpp` |
| Thomas算法(三对角矩阵) | Thomas Algorithm | `Math/Thomas Algorithm.cpp` |
| 范德蒙德矩阵 | Vandermonde Matrix | `Math/Vandermonde Matrix.cpp` |
| q-二项式系数 | q Binomial | `Math/q Binomial.cpp` |

---

## 四、数论 (Number Theory)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 贝尔数 | Bell Number | `Number Theory/Bell Number.cpp` |
| 组合数学基础 | Combinatorics Basics | `Number Theory/Combinatorics Basics.cpp` |
| 连分数 | Continued Fractions | `Number Theory/Continued Fractions.cpp` |
| 中国剩余定理 | CRT | `Number Theory/CRT.cpp` |
| 狄利克雷卷积 | Dirichlet Convolution | `Number Theory/Dirichlet Convolution.cpp` |
| 离散对数 | Discrete Log | `Number Theory/Discrete Log.cpp` |
| 离散根 | Discrete Root | `Number Theory/Discrete Root.cpp` |
| 快速离散根 | Discrete Root Faster | `Number Theory/Discrete Root Faster.cpp` |
| 扩展欧几里得算法 | Extended Euclid | `Number Theory/Extended Euclid.cpp` |
| 阶乘数系 | Factoradic Number System | `Number Theory/Factoradic Number System.cpp` |
| 费马两平方和定理 | Fermats Theorem on Sum of Two Squares | `Number Theory/Fermats Theorem on Sum of Two Squares.cpp` |
| 快速斐波那契数 | Fibonacci Number Faster | `Number Theory/Fibonacci Number Faster.cpp` |
| 等差数列的向下取整和 | Floor Sum of Arithmetic Progressions | `Number Theory/Floor Sum of Arithmetic Progressions.cpp` |
| 广义等差数列向下取整和 | Generalized Floor Sum of Arithmetic Progressions | `Number Theory/Generalized Floor Sum of Arithmetic Progressions.cpp` |
| 等差数列的交 | Intersection of Arithmetic Progressions | `Number Theory/Intersection of Arithmetic Progressions.cpp` |
| K个约数 | K Divisors | `Number Theory/K Divisors.cpp` |
| 斐波那契数的最小公倍数 | LCM of Fibonacci Numbers | `Number Theory/LCM of Fibonacci Numbers.cpp` |
| 线性同余方程 | Linear Congruence Equation | `Number Theory/Linear Congruence Equation.cpp` |
| 二元线性丢番图方程 | Linear Diophantine Equation with Two Variables | `Number Theory/Linear Diophantine Equation with Two Variables.cpp` |
| 非负解线性丢番图方程 | Linear Diophantine Equation with Nonnegative Solutions | `Number Theory/Linear Diophantine Equation with Nonnegative Solutions.cpp` |
| 三元非负解线性丢番图 | Linear Diophantine Equation Three Variables with Nonnegative Solutions | `Number Theory/Linear Diophantine Equation Three Variables with Nonnegative Solutions.cpp` |
| N未知数两方程线性丢番图 | Linear Diophantine With N Unknowns and Two Equations | `Number Theory/Linear Diophantine With N Unknowns and Two Equations.cpp` |
| 积性函数线性筛 | Linear Sieve for Multiplicative Functions | `Number Theory/Linear Sieve for Multiplicative Functions.cpp` |
| Lucas定理 | Lucas Theorem | `Number Theory/Lucas Theorem.cpp` |
| 最大互素乘积 | Maximum Coprime Product | `Number Theory/Maximum Coprime Product.cpp` |
| Min_25筛 | Min_25 Sieve | `Number Theory/Min_25 Sieve.cpp` |
| 莫比乌斯函数 | Mobius Function | `Number Theory/Mobius Function.cpp` |
| 乘法阶 | Multiplicative Order | `Number Theory/Multiplicative Order.cpp` |
| 模n的不同K次幂数目 | Number of Distinct Kth Powers Modulo n | `Number Theory/Number of Distinct Kth Powers Modulo n.cpp` |
| 基本线性代数方程的解数 | Number of Solutions to a Basic Linear Algebraic Equation | `Number Theory/Number of Solutions to a Basic Linear Algebraic Equation.cpp` |
| 带变量上界约束的基本线性代数方程的解数 | Number of Solutions to a Basic Linear Algebraic Equation with Variable Upper Bound Constraints | `Number Theory/Number of Solutions to a Basic Linear Algebraic Equation with Variable Upper Bound Constraints.cpp` |
| x^2 ≡ 1 (mod m) 的解数 | Number of Solutions to x^2 = 1 mod m | `Number Theory/Number of Solutions to x^2 = 1 mod m.cpp` |
| 区间内 ax%p 的数目 | Number of ax%p in a Range | `Number Theory/Number of ax%p in a Range.cpp` |
| ax+by=c 的非负整数解数 | Number of Nonnegative Integer Solutions to ax+by = c | `Number Theory/Number of Nonnegative Integer Solutions to ax+by = c.cpp` |
| 分拆函数 | Partition Function | `Number Theory/Partition Function.cpp` |
| 欧拉函数场 | Phi Field | `Number Theory/Phi Field.cpp` |
| 欧拉函数 | Phi Function | `Number Theory/Phi Function.cpp` |
| Pisano周期 | Pisano Period | `Number Theory/Pisano Period.cpp` |
| Pollard Rho质因数分解 | Pollard Rho | `Number Theory/Pollard Rho.cpp` |
| 幂塔 | Power Tower | `Number Theory/Power Tower.cpp` |
| nCi的前缀和查询 | Prefix Sum Queries of nCi | `Number Theory/Prefix Sum Queries of nCi.cpp` |
| 素数基 | Prime Basis | `Number Theory/Prime Basis.cpp` |
| 素数计数函数 | Prime Counting Function | `Number Theory/Prime Counting Function.cpp` |
| 快速质因数分解 | Prime Factorization Fastest | `Number Theory/Prime Factorization Fastest.cpp` |
| 素数系统 | Prime Number System | `Number Theory/Prime Number System.cpp` |
| 原根 | Primitive Root | `Number Theory/Primitive Root.cpp` |
| 有理逼近 | Rational Approximation | `Number Theory/Rational Approximation.cpp` |
| 素数筛 | Sieve | `Number Theory/Sieve.cpp` |
| 1e9素数筛 | Sieve upto 1e9 | `Number Theory/Sieve upto 1e9.cpp` |
| 满足 l ≤ ax % p ≤ r 的最小非负整数x | Smallest Nonnegative Integer x s.t. l ≤ ax % p ≤ r | `Number Theory/Smallest Nonnegative Integer x s.t. l ≤ ax % p ≤ r.cpp` |
| 恰好有K个约数的最小数 | Smallest Number Having Exactly K Divisors | `Number Theory/Smallest Number Having Exactly K Divisors.cpp` |
| 固定k的第一类斯特林数 | Stirling Number of the First Kind for Fixed k | `Number Theory/Stirling Number of the First Kind for Fixed k.cpp` |
| 固定n的第一类斯特林数 | Stirling Number of the First Kind for Fixed n | `Number Theory/Stirling Number of the First Kind for Fixed n.cpp` |
| 固定k的第二类斯特林数 | Stirling Number of the Second Kind for Fixed k | `Number Theory/Stirling Number of the Second Kind for Fixed k.cpp` |
| 固定n的第二类斯特林数 | Stirling Number of the Second Kind for Fixed n | `Number Theory/Stirling Number of the Second Kind for Fixed n.cpp` |
| 等差数列的模和与除和 | Sum of Arithmetic Progression Modular and Divided | `Number Theory/Sum of Arithmetic Progression Modular and Divided.cpp` |
| 等差数列幂的除和 | Sum of Arithmetic Progression Powers Divided | `Number Theory/Sum of Arithmetic Progression Powers Divided.cpp` |
| 1到n的C(a(i), k)之和 | Sum of C(a(i), k) for each k from 1 to n | `Number Theory/Sum of C(a(i), k) for each k from 1 to n.cpp` |
| 向下取整之和 | Sum of Floors | `Number Theory/Sum of Floors.cpp` |
| 固定大n的nCi之和 | Sum of nCi for a Fixed Large n | `Number Theory/Sum of nCi for a Fixed Large n.cpp` |
| 固定同余类的nCi之和 | Sum of nCi over a Fixed Congruence Class | `Number Theory/Sum of nCi over a Fixed Congruence Class.cpp` |
| cbrt(n)内的约数个数之和 | Sum of The Number of Divisors in cbrt(n) | `Number Theory/Sum of The Number of Divisors in cbrt(n).cpp` |
| Tonelli-Shanks算法 | Tonelli Shanks Algorithm | `Number Theory/Tonelli Shanks Algorithm.cpp` |
| 任意模的组合数 | nCr Modulo Any Mod | `Number Theory/nCr Modulo Any Mod.cpp` |

---

## 五、字符串 (Strings)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| AC自动机 | Aho Corasick | `Strings/Aho Corasick.cpp` |
| AC自动机所有对出现关系 | Aho Corasick All Pair Occurrence Relation | `Strings/Aho Corasick All Pair Occurrence Relation.cpp` |
| 动态AC自动机 | Aho Corasick Dynamic | `Strings/Aho Corasick Dynamic.cpp` |
| 所有子串的最长公共子序列 | All Substring Longest Common Subsequence | `Strings/All Substring Longest Common Subsequence.cpp` |
| 位运算LCS | Bit LCS | `Strings/Bit LCS.cpp` |
| 循环LCS | Cyclic LCS | `Strings/Cyclic LCS.cpp` |
| De Bruijn序列 | De Bruijn Sequence | `Strings/De Bruijn Sequence.cpp` |
| KMP算法 | KMP | `Strings/KMP.cpp` |
| Manacher回文算法 | Manachers | `Strings/Manachers.cpp` |
| 区间内的回文数 | Number of Palindromes in Range | `Strings/Number of Palindromes in Range.cpp` |
| 回文树 | Palindromic Tree | `Strings/Palindromic Tree.cpp` |
| 可持久化回文树 | Palindromic Tree Persistent | `Strings/Palindromic Tree Persistent.cpp` |
| 前缀自动机 | Prefix Automaton | `Strings/Prefix Automaton.cpp` |
| 字符串哈希 | String Hashing | `Strings/String Hashing.cpp` |
| 二维字符串哈希 | String Hashing 2D | `Strings/String Hashing 2D.cpp` |
| 带更新和翻转的字符串哈希 | String Hashing With Updates and Reverse | `Strings/String Hashing With Updates and Reverse.cpp` |
| 使用位集的字符串匹配 | String Matching using Bitsets | `Strings/String Matching using Bitsets.cpp` |
| 使用FFT的字符串匹配 | String Matching With FFT | `Strings/String Matching With FFT.cpp` |
| 后缀数组 | Suffix Array | `Strings/Suffix Array.cpp` |
| 同构后缀数组 | Suffix Array Isomorphic | `Strings/Suffix Array Isomorphic.cpp` |
| 后缀自动机 | Suffix Automaton | `Strings/Suffix Automaton.cpp` |
| 区间内不同子串查询的后缀自动机 | Suffix Automaton Distinct Substring Queries in Range | `Strings/Suffix Automaton Distinct Substring Queries in Range.cpp` |
| Z算法 | Z Algorithm | `Strings/Z Algorithm.cpp` |

---

## 六、动态规划优化 (Dynamic Programming Optimizations)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 1D1D动态规划 | 1D1D DP | `Dynamic Programming Optimizations/1D1D DP.cpp` |
| 多重背包 | Bounded Knapsack | `Dynamic Programming Optimizations/Bounded Knapsack.cpp` |
| 连通分量DP | Connected Component DP | `Dynamic Programming Optimizations/Connected Component DP.cpp` |
| 凸包优化 | Convex Hull Trick | `Dynamic Programming Optimizations/Convex Hull Trick.cpp` |
| 数位DP | Digit DP | `Dynamic Programming Optimizations/Digit DP.cpp` |
| 约数上的DP | DP Over Divisors | `Dynamic Programming Optimizations/DP Over Divisors.cpp` |
| 分治优化 | Divide and Conquer Optimization | `Dynamic Programming Optimizations/Divide and Conquer Optimization.cpp` |
| 动态凸包优化 | Dynamic Convex Hull Trick | `Dynamic Programming Optimizations/Dynamic Convex Hull Trick.cpp` |
| 动态子掩码计数 | Dynamic Submask Count | `Dynamic Programming Optimizations/Dynamic Submask Count.cpp` |
| Hirschberg算法 | Hirschbergs Algorithm | `Dynamic Programming Optimizations/Hirschbergs Algorithm.cpp` |
| Knuth优化 | Knuth Optimization | `Dynamic Programming Optimizations/Knuth Optimization.cpp` |
| 李超线段树 | Li Chao Tree | `Dynamic Programming Optimizations/Li Chao Tree.cpp` |
| 乘积至少为K的子序列数目 | Number of Subsequences Having Product at least K | `Dynamic Programming Optimizations/Number of Subsequences Having Product at least K.cpp` |
| 可持久化凸包优化 | Persistent CHT | `Dynamic Programming Optimizations/Persistent CHT.cpp` |
| 可持久化李超线段树 | Persistent Li Chao Tree | `Dynamic Programming Optimizations/Persistent Li Chao Tree.cpp` |
| 子集和卷积 | SOS convolutions | `Dynamic Programming Optimizations/SOS convolutions.cpp` |
| SQRT时间子集和 | Subset Sum in SQRT | `Dynamic Programming Optimizations/Subset Sum in SQRT.cpp` |
| 位集的子集并 | Subset Union of Bitsets | `Dynamic Programming Optimizations/Subset Union of Bitsets.cpp` |
| 异或方程 | XOR Equation | `Dynamic Programming Optimizations/XOR Equation.cpp` |
| x² + 1 技巧 | x² + 1 trick | `Dynamic Programming Optimizations/x² + 1 trick.cpp` |

---

## 七、计算几何 (Geometry)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 所有对线段交 | All Pair Segment Intersection | `Geometry/All Pair Segment Intersection.cpp` |
| 最近点对 | Closest Pair of Points | `Geometry/Closest Pair of Points.cpp` |
| 动态凸包 | Convec Hull Dynamic | `Geometry/Convec Hull Dynamic.cpp` |
| Delaunay三角剖分 | Delaunay Triangulation | `Geometry/Delaunay Triangulation.cpp` |
| 2D几何 | Geometry 2D | `Geometry/Geometry 2D.cpp` |
| 3D几何 | Geometry 3D | `Geometry/Geometry 3D.cpp` |
| 半平面交 | Half Plane Intersection | `Geometry/Half Plane Intersection.cpp` |
| 动态半平面交 | Half Plane Intersection Dynamic | `Geometry/Half Plane Intersection Dynamic.cpp` |
| 给定边长的最大三角形面积 | Maximum Area of Triangle, Given are Lengths | `Geometry/Maximum Area of Triangle, Given are Lengths.cpp` |
| 洋葱分解 | Onion Decomposition | `Geometry/Onion Decomposition.cpp` |
| 点定位 | Point Location | `Geometry/Point Location.cpp` |
| Voronoi图 | Voronoi Diagram | `Geometry/Voronoi Diagram.cpp` |

---

## 八、博弈论 (Game Theory)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| Alpha-Beta剪枝 | Alpha Beta Pruning | `Game Theory/Alpha Beta Pruning.cpp` |
| 红蓝Hackenbush | Blue Red Hackenbush | `Game Theory/Blue Red Hackenbush.cpp` |
| 绿Hackenbush | Green Hackenbush | `Game Theory/Green Hackenbush.cpp` |
| 图上的匹配游戏 | Matching Game On A Graph | `Game Theory/Matching Game On A Graph.cpp` |

---

## 九、杂项 (Miscellaneous)

| 中文名称 | 英文名称 | 文件路径 |
|---------|---------|---------|
| 大整数 | BigInt | `Miscellaneous/BigInt.cpp` |
| 自定义位集 | Bitset Custom | `Miscellaneous/Bitset Custom.cpp` |
| 日期处理 | Dates | `Miscellaneous/Dates.cpp` |
| 表达式解析 | Expression Parsing | `Miscellaneous/Expression Parsing.cpp` |
| 分数二分 | Fraction Binary Search | `Miscellaneous/Fraction Binary Search.cpp` |
| 格雷码 | Gray Code | `Miscellaneous/Gray Code.cpp` |
| 约瑟夫问题 | Josephus Problem | `Miscellaneous/Josephus Problem.cpp` |
| 排列的k次根 | K-th Root of a Permutation | `Miscellaneous/K-th Root of a Permutation.cpp` |
| 无限网格上马的移动 | Knight Moves in Infinity Grid | `Miscellaneous/Knight Moves in Infinity Grid.cpp` |
| 所有子数组的MEX | MEX of all Subarrays | `Miscellaneous/MEX of all Subarrays.cpp` |
| 拟阵交-着色图拟阵 | Matroid Intersection Color Graphic Matroid | `Miscellaneous/Matroid Intersection Color Graphic Matroid.cpp` |
| 拟阵交-着色线性拟阵 | Matroid Intersection Color Linear Matroid | `Miscellaneous/Matroid Intersection Color Linear Matroid.cpp` |
| 树中K个节点的所有对距离和的最大值 | Maximum of Sum of All Pair Distances of K nodes in a Tree | `Miscellaneous/Maximum of Sum of All Pair Distances of K nodes in a Tree.cpp` |
| 负进制(二进制) | Negative Base (Binary) | `Miscellaneous/Negative Base (Binary).cpp` |
| 并行二分搜索 | Parallel Binary Search | `Miscellaneous/Parallel Binary Search.cpp` |
| Schreier-Sims算法 | Schreier–Sims algorithm | `Miscellaneous/Schreier–Sims algorithm.cpp` |
| 代码本去空格 | Space Remover For Codebook | `Miscellaneous/Space Remover For Codebook.cpp` |
| 压力测试 | Stress Testing | `Miscellaneous/Stress Testing.cpp` |
| 位集的子集并 | Subset Union of Bitsets | `Miscellaneous/Subset Union of Bitsets.cpp` |
| Trygub数 | Trygub Num | `Miscellaneous/Trygub Num.cpp` |
| 任意范围异或方程 | XOR Equation Arbitrary Range | `Miscellaneous/XOR Equation Arbitrary Range.cpp` |

---

## 📊 统计信息

| 分类 | 文件数量 |
|-----|---------|
| 数据结构 (Data Structures) | 78 |
| 图论 (Graph Theory) | 103 |
| 数学 (Math) | 65 |
| 数论 (Number Theory) | 75 |
| 字符串 (Strings) | 30 |
| 动态规划优化 (Dynamic Programming Optimizations) | 25 |
| 计算几何 (Geometry) | 14 |
| 博弈论 (Game Theory) | 4 |
| 杂项 (Miscellaneous) | 23 |
| **总计** | **约 520** |

---

## 🔍 快速查找指南

### 按中文关键词查找

| 想找的中文概念 | 英文名称 | 所在分类 |
|--------------|---------|---------|
| 线段树 | Segment Tree | 数据结构 |
| 树状数组 | BIT / Fenwick | 数据结构 |
| 并查集 | DSU / UnionFind | 数据结构 |
| 后缀自动机 | Suffix Automaton | 字符串 |
| 后缀数组 | Suffix Array | 字符串 |
| 最短路 | Dijkstra / Bellman Ford / Floyd | 图论 |
| 最小生成树 | Kruskal / Prim | 图论 |
| 最大流 | Dinics Algorithm | 图论 |
| 二分图匹配 | HopCroft Karp | 图论 |
| FFT | FFT | 数学 |
| NTT | NTT | 数学 |
| 快速幂 | Matrix Exponentiation | 数学 |
