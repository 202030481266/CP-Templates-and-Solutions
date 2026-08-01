// gen.cpp —— 随机树 / 随机图生成器，用于对拍构造测试数据
// 编译：g++ -O2 -std=c++17 gen.cpp -o gen
// 运行：./gen <seed> > input.txt   （不同 seed 生成不同数据，方便复现某次出错的数据）
//
// 使用方式：在 main() 里根据你要测的题目，调用对应的生成函数即可。
// 下面提供的函数覆盖了对拍中最常用的几类数据形态。

#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng;

// 生成闭区间 [l, r] 内的随机整数
long long randInt(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// ======================= 树的生成 =======================

// 生成一棵 n 个节点的随机树，返回边集 (fa, son)，节点编号 1~n
// method = 0：每个节点 i(i>=2) 随机选 [1, i-1] 中的一个点当父亲 —— 实现简单，但偏向"菊花图"（浅而宽）
// method = 1：父亲范围限制为 [max(1, i-range), i-1] —— range 越小树越接近链状，越大越接近随机/菊花状，可以精细控制树的形状
// method = 2：Prüfer 序列构造 —— 严格等概率生成所有 n^(n-2) 种标号树，是最"均匀随机"的写法
vector<pair<int,int>> genRandomTree(int n, int method = 1, int range = -1) {
    vector<pair<int,int>> edges;
    if (n <= 1) return edges;

    if (method == 0) {
        for (int i = 2; i <= n; i++) {
            int fa = randInt(1, i - 1);
            edges.push_back({fa, i});
        }
    } else if (method == 1) {
        int R = (range == -1) ? n : range;
        for (int i = 2; i <= n; i++) {
            int lo = max(1, i - R);
            int fa = randInt(lo, i - 1);
            edges.push_back({fa, i});
        }
    } else { // method == 2, Prufer 序列
        if (n == 2) { edges.push_back({1, 2}); return edges; }
        vector<int> prufer(n - 2);
        for (auto &x : prufer) x = randInt(1, n);

        vector<int> degree(n + 1, 1);
        for (int x : prufer) degree[x]++;

        priority_queue<int, vector<int>, greater<int>> leaves; // 小顶堆存当前度数为1的点
        for (int i = 1; i <= n; i++) if (degree[i] == 1) leaves.push(i);

        for (int x : prufer) {
            int leaf = leaves.top(); leaves.pop();
            edges.push_back({leaf, x});
            if (--degree[leaf] == 0) {} // 叶子用掉了
            if (--degree[x] == 1) leaves.push(x);
        }
        int u = leaves.top(); leaves.pop();
        int v = leaves.top(); leaves.pop();
        edges.push_back({u, v});
    }
    return edges;
}

// 链（一条直线，最容易卡"树退化为链"的情况，比如线段树/树剖的复杂度）
vector<pair<int,int>> genChain(int n) {
    vector<pair<int,int>> edges;
    for (int i = 2; i <= n; i++) edges.push_back({i - 1, i});
    return edges;
}

// 菊花图（一个中心点连所有其它点，卡"暴力枚举子树/DFS 递归深度小但度数大"的情况）
vector<pair<int,int>> genStar(int n, int center = 1) {
    vector<pair<int,int>> edges;
    for (int i = 1; i <= n; i++) if (i != center) edges.push_back({center, i});
    return edges;
}

// 完全二叉树
vector<pair<int,int>> genBinaryTree(int n) {
    vector<pair<int,int>> edges;
    for (int i = 2; i <= n; i++) edges.push_back({i / 2, i});
    return edges;
}

// 毛毛虫树：一条长度为 spineLen 的主链，其余节点随机挂在主链上（介于链和菊花之间的形态）
vector<pair<int,int>> genCaterpillar(int n, int spineLen) {
    vector<pair<int,int>> edges;
    spineLen = min(spineLen, n);
    for (int i = 2; i <= spineLen; i++) edges.push_back({i - 1, i});
    for (int i = spineLen + 1; i <= n; i++) {
        int fa = randInt(1, spineLen);
        edges.push_back({fa, i});
    }
    return edges;
}

// 把节点编号 1~n 随机重新映射一遍。
// 强烈建议对生成的树都调用一次：否则边总是 (较小编号 -> 较大编号)，
// 如果被测程序里对编号大小做了隐藏假设，这种"整齐"的数据反而测不出 bug。
vector<pair<int,int>> shuffleLabels(vector<pair<int,int>> edges, int n) {
    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end(), rng);
    for (auto &e : edges) {
        e.first = perm[e.first];
        e.second = perm[e.second];
    }
    return edges;
}

// ======================= 图的生成 =======================

// 通用随机图：n 个点，m 条边
// allowSelfLoop：是否允许自环；allowMultiEdge：是否允许重边；directed：是否有向
// 注意：不保证连通！如果题目要求连通图，请用 genConnectedGraph
vector<pair<int,int>> genRandomGraph(int n, int m, bool allowSelfLoop = false,
                                      bool allowMultiEdge = false, bool directed = false) {
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;

    long long maxEdges;
    if (directed) maxEdges = allowSelfLoop ? (long long)n * n : (long long)n * (n - 1);
    else          maxEdges = allowSelfLoop ? (long long)n * (n + 1) / 2 : (long long)n * (n - 1) / 2;
    if (!allowMultiEdge) m = (int)min((long long)m, maxEdges); // 防止死循环

    while ((int)edges.size() < m) {
        int u = (int)randInt(1, n), v = (int)randInt(1, n);
        if (!allowSelfLoop && u == v) continue;
        auto key = (!directed && u > v) ? make_pair(v, u) : make_pair(u, v);
        if (!allowMultiEdge && used.count(key)) continue;
        used.insert(key);
        edges.push_back({u, v});
    }
    return edges;
}

// 保证连通的随机图：先生成一棵随机树打底（保证连通），再随机加边补到 m 条
vector<pair<int,int>> genConnectedGraph(int n, int m, bool directed = false) {
    vector<pair<int,int>> edges = genRandomTree(n, 1);
    m = max(m, n - 1);

    set<pair<int,int>> used;
    for (auto e : edges) {
        auto key = (e.first > e.second) ? make_pair(e.second, e.first) : e;
        used.insert(key);
    }

    int remain = m - (n - 1);
    int attempts = 0, maxAttempts = remain * 20 + 1000; // 边接近稠密时随机碰撞概率变高，限制尝试次数防止死循环
    while (remain > 0 && attempts < maxAttempts) {
        attempts++;
        int u = (int)randInt(1, n), v = (int)randInt(1, n);
        if (u == v) continue;
        auto key = (!directed && u > v) ? make_pair(v, u) : make_pair(u, v);
        if (used.count(key)) continue;
        used.insert(key);
        edges.push_back({u, v});
        remain--;
    }
    return edges;
}

// 有向无环图（DAG）：n 个点，m 条边。做法是只允许编号从小指向大，天然无环
vector<pair<int,int>> genDAG(int n, int m) {
    vector<pair<int,int>> edges;
    set<pair<int,int>> used;
    long long maxEdges = (long long)n * (n - 1) / 2;
    m = (int)min((long long)m, maxEdges);

    while ((int)edges.size() < m) {
        int u = (int)randInt(1, n), v = (int)randInt(1, n);
        if (u >= v) continue;
        if (used.count({u, v})) continue;
        used.insert({u, v});
        edges.push_back({u, v});
    }
    return edges;
}

// 给已有的 m 条边生成随机权值 [minW, maxW]
vector<long long> genWeights(int m, long long minW, long long maxW) {
    vector<long long> w(m);
    for (auto &x : w) x = randInt(minW, maxW);
    return w;
}

// ======================= 输出 =======================

// 打印边集。randomizeDirection：是否随机交换每条边的 u,v 顺序打印
// 注意：对"有方向意义"的边（比如 DAG、有根树的父子关系）不要开这个选项，否则会破坏语义！
void printEdges(int n, vector<pair<int,int>> edges, bool shuffleEdgeOrder = true,
                 bool randomizeDirection = true, bool printN = true) {
    if (shuffleEdgeOrder) shuffle(edges.begin(), edges.end(), rng);
    if (printN) cout << n << " " << edges.size() << "\n";
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (randomizeDirection && randInt(0, 1)) swap(u, v);
        cout << u << " " << v << "\n";
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 用法：./gen <seed> [其他参数]
    // 对拍脚本里每轮换一个 seed 调用本程序，就能得到不同的随机数据；
    // 一旦某个 seed 使被测程序出错，把这个 seed 记下来就能稳定复现。
    unsigned long long seed = (argc > 1) ? stoull(argv[1])
        : chrono::steady_clock::now().time_since_epoch().count();
    rng.seed(seed);

    // ------------------- 下面是几个使用示例，按需修改/取消注释 -------------------

    int n = 5000;

    // 示例1：均匀随机树（Prüfer 序列），并打乱节点编号
    auto tree = genRandomTree(n, 2);
    tree = shuffleLabels(tree, n);
    printEdges(n, tree);

    // 示例2：偏"胖"的随机树（父亲范围放宽），链状树（range 较小）
    // auto tree2 = genRandomTree(n, 1, /*range=*/3);

    // 示例3：链 / 菊花 / 二叉树 / 毛毛虫
    // auto chain = genChain(n);
    // auto star  = genStar(n);
    // auto bt    = genBinaryTree(n);
    // auto cat   = genCaterpillar(n, /*spineLen=*/n / 2);

    // 示例4：随机图（不保证连通），允许/禁止自环、重边、有向
    // auto g = genRandomGraph(n, 15, /*allowSelfLoop=*/false, /*allowMultiEdge=*/false, /*directed=*/false);
    // printEdges(n, g);

    // 示例5：保证连通的随机图
    // auto cg = genConnectedGraph(n, n + 5);
    // printEdges(n, cg);

    // 示例6：DAG（拓扑序天然存在，编号小的指向编号大的）
    // auto dag = genDAG(n, 15);
    // printEdges(n, dag, true, /*randomizeDirection=*/false); // DAG 不能随便交换方向！

    // 示例7：给边加随机权值
    // auto w = genWeights((int)tree.size(), 1, 100);
    // for (int i = 0; i < (int)tree.size(); i++)
    //     cout << tree[i].first << " " << tree[i].second << " " << w[i] << "\n";

    return 0;
}