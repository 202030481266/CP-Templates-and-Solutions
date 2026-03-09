#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 9;
const int N = 300005;

long long f[N]; // 预处理的标准斐波那契数列

// 预处理斐波那契数列
void init_fib() {
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; i < N; i++) {
        f[i] = (f[i - 1] + f[i - 2]) % MOD;
    }
}

// ---------------- 核心数学工具 ----------------

// 已知数列的前两项是 t1 和 t2，求它的第 k 项 (k >= 1)
long long calc_term(long long t1, long long t2, int k) {
    if (k == 1) return t1;
    if (k == 2) return t2;
    // 根据推导公式: G_k = t1 * f[k-2] + t2 * f[k-1]
    return (t1 * f[k - 2] % MOD + t2 * f[k - 1] % MOD) % MOD;
}

// 已知数列的前两项是 t1 和 t2，求它的前 k 项之和 (k >= 1)
long long calc_sum(long long t1, long long t2, int k) {
    if (k == 0) return 0;
    if (k == 1) return t1;
    // 根据性质: Sum(1...k) = G_{k+2} - G_2
    long long term_k_plus_2 = calc_term(t1, t2, k + 2);
    return (term_k_plus_2 - t2 + MOD) % MOD;
}

// ---------------- 线段树定义 ----------------

struct Node {
    long long sum;
    long long tag1; // 延迟标记：当前区间第一个位置应该加的值
    long long tag2; // 延迟标记：当前区间第二个位置应该加的值
} tree[N << 2];

long long a[N]; // 初始数组

// 将 tag 应用于当前节点
void apply(int node, long long t1, long long t2, int len) {
    // 1. 更新当前节点的区间和
    tree[node].sum = (tree[node].sum + calc_sum(t1, t2, len)) % MOD;
    
    // 2. 将 t1, t2 累加到当前节点的 tag 上
    tree[node].tag1 = (tree[node].tag1 + t1) % MOD;
    tree[node].tag2 = (tree[node].tag2 + t2) % MOD;
}

// 向上合并信息
void push_up(int node) {
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % MOD;
}

// 向下传递延迟标记
void push_down(int node, int l, int r) {
    if (tree[node].tag1 == 0 && tree[node].tag2 == 0) return;

    int mid = (l + r) / 2;
    int left_len = mid - l + 1;
    int right_len = r - mid;

    long long t1 = tree[node].tag1;
    long long t2 = tree[node].tag2;

    // 左儿子：起手式完全一样，直接把 t1, t2 传给它
    apply(node * 2, t1, t2, left_len);

    // 右儿子：起手式是整个数列的第 left_len + 1 项和第 left_len + 2 项
    long long right_t1 = calc_term(t1, t2, left_len + 1);
    long long right_t2 = calc_term(t1, t2, left_len + 2);
    apply(node * 2 + 1, right_t1, right_t2, right_len);

    // 清空当前节点的标记
    tree[node].tag1 = 0;
    tree[node].tag2 = 0;
}

// 建树
void build(int node, int l, int r) {
    if (l == r) {
        tree[node].sum = a[l] % MOD;
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

// 区间更新：在 [ql, qr] 范围内加上标准的斐波那契数列
void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        // 计算当前节点区间 [l, r] 相对于查询起点 ql 的偏移量
        int offset = l - ql + 1;
        // 这一段需要加的斐波那契数列的首两项，正好是标准斐波那契的第 offset 和 offset+1 项
        apply(node, f[offset], f[offset + 1], r - l + 1);
        return;
    }
    
    push_down(node, l, r); // 必须先下放标记
    
    int mid = (l + r) / 2;
    if (ql <= mid) update(node * 2, l, mid, ql, qr);
    if (qr > mid)  update(node * 2 + 1, mid + 1, r, ql, qr);
    
    push_up(node);
}

// 区间查询：求 [ql, qr] 的区间和
long long query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[node].sum;
    
    push_down(node, l, r);
    
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) res = (res + query(node * 2, l, mid, ql, qr)) % MOD;
    if (qr > mid)  res = (res + query(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
    
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fib();

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);

    while (m--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            update(1, 1, n, l, r);
        } else {
            cout << query(1, 1, n, l, r) << "\n";
        }
    }

    return 0;
}