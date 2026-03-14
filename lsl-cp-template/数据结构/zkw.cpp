#include <iostream>

const int MAXN = 100005; 
const int INF = 2e9; // 根据你的数据范围调整，用于表示负无穷

int tree[MAXN << 2]; // 树数组，大小开到原数组的 4 倍是绝对安全的
int M;               // 叶子节点的起始偏移量

// 手写 max 避免依赖 algorithm 库（如果你喜欢可以用 std::max）
inline int max(int a, int b) {
    return a > b ? a : b;
}

// 1. 建树操作：O(n)
// n 是数组实际大小，a 是原数组（下标从 1 开始）
void build(int n, int* a) {
    // 找到第一个大于等于 n+2 的 2 的幂
    // 加 2 是为了给开区间查询留出最左和最右的“空节点”哨兵
    for (M = 1; M <= n + 1; M <<= 1);
    
    // 清空树数组（如果需要多次跑测试用例，这一步很重要）
    for (int i = 0; i <= (M << 1); ++i) tree[i] = -INF;

    // 将原数组的数据放入叶子节点
    for (int i = 1; i <= n; ++i) {
        tree[M + i] = a[i];
    }
    
    // 自底向上维护父节点的信息
    for (int i = M - 1; i >= 1; --i) {
        // tree[i << 1] 是左儿子，tree[i << 1 | 1] 是右儿子
        tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
}

// 2. 单点修改：O(log n)
// 将原数组第 x 个位置的值修改为 val (变大变小都可以)
void update(int x, int val) {
    // 直接定位到叶子节点，并修改
    x += M;
    tree[x] = val;
    
    // 自底向上更新直到根节点 (x = 1)
    for (x >>= 1; x; x >>= 1) {
        tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
    }
}

// 3. 区间最大值查询：O(log n)
// 查询闭区间 [L, R] 的最大值
int query(int L, int R) {
    int ans = -INF;
    // ZKW 核心逻辑：将闭区间 [L, R] 转化为开区间 (L-1, R+1)
    for (L = L + M - 1, R = R + M + 1; L ^ R ^ 1; L >>= 1, R >>= 1) {
        // ~L & 1 等价于 L % 2 == 0 (L 是左儿子)，则其右兄弟 L^1 属于查询区间
        if (~L & 1) ans = max(ans, tree[L ^ 1]);
        // R & 1 等价于 R % 2 == 1 (R 是右儿子)，则其左兄弟 R^1 属于查询区间
        if ( R & 1) ans = max(ans, tree[R ^ 1]);
    }
    return ans;
}