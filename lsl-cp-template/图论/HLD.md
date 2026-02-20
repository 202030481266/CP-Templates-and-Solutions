# 🌲 树链剖分 (HLD) 实战手册

本手册基于轻重边剖分，结合线段树，将树上问题转化为数组上的区间问题。核心时间复杂度为：单次路径操作 ，单次子树操作 。

## 1. 核心概念速查

为了让你在魔改模板时不迷路，这里列出核心变量的物理意义：

| 变量/数组 | 物理意义 | 作用 |
| --- | --- | --- |
| `g[u]` | 邻接表 | 存储树的结构。预处理后，**`g[u][0]` 永远是 `u` 的重儿子**。 |
| `st[u]` | DFS 序进入时间戳 | **节点 `u` 在线段树中的真实下标。** |
| `en[u]` | DFS 序离开时间戳 | 以 `u` 为根的子树，在线段树中对应的区间是 `[st[u], en[u]]`。 |
| `head[u]` | 重链头 | 节点 `u` 所在重链的顶端节点。用于在不同重链之间“向上跳”。 |
| `dep[u]` | 节点深度 | 用于判断在同一条重链上时，谁是祖先（深度小的在上面）。 |

---

## 2. 增强版模板补充代码

建议将以下两个函数加入到你的模板中。这是 HLD 最经典的**对称跳链法**，可以直接替换掉你原来复杂的 `lca` 结合 `kth` 的查询方式，并且补齐了路径修改功能。

```cpp
// 🌟 补充 1：树上路径区间修改 (u 到 v 路径上的所有节点加上 val)
void upd_path(int u, int v, int val) {
    // 当两个点不在同一条重链上时，让所在重链头深度更大的那个点往上跳
    while (head[u] != head[v]) {
        if (dep[head[u]] < dep[head[v]]) swap(u, v);
        // 更新较深节点 u 到它所在重链头 head[u] 的这一段连续区间
        t.upd(1, 1, n, st[head[u]], st[u], val);
        // u 跳到重链头的父节点（即进入了上一条链）
        u = par[head[u]][0];
    }
    // 当两个点跳到同一条重链上时，更新它们之间的区间
    if (dep[u] < dep[v]) swap(u, v); // 保证 u 的深度大于 v
    t.upd(1, 1, n, st[v], st[u], val); // v 是 u 的祖先，st[v] 更小
}

// 🌟 补充 2：树上路径区间查询 (查询 u 到 v 路径上的最大值)
int query_path(int u, int v) {
    int ans = -inf;
    while (head[u] != head[v]) {
        if (dep[head[u]] < dep[head[v]]) swap(u, v);
        ans = max(ans, t.query(1, 1, n, st[head[u]], st[u]));
        u = par[head[u]][0];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ans = max(ans, t.query(1, 1, n, st[v], st[u]));
    return ans;
}

```

---

## 3. 标准调用流程 (Main 函数 Boilerplate)

在任何一道 HLD 题目中，`main` 函数的前置处理几乎都是固定的，请严格按照以下 5 步执行：

```cpp
int main() {
    // 0. (多测清空) 如果有多个 test case，必须在这里重置 T=0，清空 g, st, en, t 等！
    T = 0; 
    
    // 1. 读入树
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    
    // 2. 第一遍 DFS：求出 sz, dep, par，并将重儿子交换到 g[u][0]
    dfs(1); 
    
    // 3. 设置根节点的重链头
    head[1] = 1; 
    
    // 4. 第二遍 DFS：打时间戳 st, en，记录 head
    dfs_hld(1); 
    
    // 5. 初始化线段树 (根据 st 数组映射的具体点权建树)
    t.build(1, 1, n); 
    
    // --- 之后就可以随心所欲调用 API 了 ---
}

```

---

## 4. 全场景 API 调用指南

### 场景 A：子树操作 (Subtree Operations)

由于 HLD 保证了一棵子树内的所有节点的 `st` 戳是连续的一段区间，直接操作 `[st[u], en[u]]` 即可。

* **子树加上 **：`t.upd(1, 1, n, st[u], en[u], v);`
* **查询子树最大值**：`t.query(1, 1, n, st[u], en[u]);`

### 场景 B：路径操作 (Path Operations)

利用前面补充的对称跳链函数。

* **路径上所有节点加上 **：`upd_path(u, v, val);`
* **查询路径最大值**：`query_path(u, v);`

### 场景 C：单点操作 (Point Operations)

单点其实就是长度为 1 的区间。

* **节点  加上 **：`t.upd(1, 1, n, st[u], st[u], v);`
* **查询节点  的值**：`t.query(1, 1, n, st[u], st[u]);`

---

## 5. 线段树魔改速查表 (Cheat Sheet)

目前的线段树是 **区间加法 + 区间求最大值**。如果题目变了，你需要改线段树的这三个地方：

| 需求场景 | 修改 `ST::combine(a, b)` | 修改 `ST::pull(n)` | 修改 `ST::push(n, b, e)` 懒标记下推 |
| --- | --- | --- | --- |
| **求最大值** (当前) | `return max(a, b);` | `t[n] = max(t[lc], t[rc]);` | `t[n] = t[n] + lazy[n];` |
| **求最小值** | `return min(a, b);` | `t[n] = min(t[lc], t[rc]);` | `t[n] = t[n] + lazy[n];` *(注意初始值赋为 inf)* |
| **求区间和** | `return a + b;` | `t[n] = t[lc] + t[rc];` | `t[n] = t[n] + lazy[n] * (e - b + 1);` |
| **区间赋值为 ** | 视需求 (max/min/sum) | 视需求 | `lazy` 含义变为覆盖，`t[n] = lazy[n]` 或 `t[n] = lazy[n] * (e - b + 1)` |

*(注意：如果是区间和，`t` 数组和返回值可能需要开 `long long` 即 `int64_t`)*

---

## 6. 避坑指南 (Troubleshooting)

1. **节点权重初始化**：目前的 `t.build` 只是把线段树清零。如果题目一开始节点就有初始权重（比如数组 `W[1...n]`），你需要映射到线段树里：在 `t.build` 的 `b == e` 时刻，写 `t[n] = W[映射回原节点的编号]`。
* *提示*：为了实现这点，你需要一个反向映射数组 `rev[st[u]] = u;`，在 `dfs_hld` 时记录，然后在 `build` 里写 `t[n] = W[rev[b]];`。


2. **根节点非 1**：题目如果指定了根节点 ，`dfs(R, 0)` 和 `dfs_hld(R)` 必须传 。
3. **边权转点权**：目前的模板是处理**点权**的。如果题目给的是**树上的边权**，需要将边权下放到深度更深的那个节点上转化为点权。
