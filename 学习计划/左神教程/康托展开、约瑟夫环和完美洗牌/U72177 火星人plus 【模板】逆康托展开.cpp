#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 常量
const int MAX_N = 1e5;  // 根据需要调整

// 预计算阶乘
long long factorials[MAX_N + 1];

// Fenwick 树（Binary Indexed Tree）实现
class FenwickTree {
public:
    vector<int> tree;
    int n;

    FenwickTree(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    // 在位置 idx 增加 delta
    void update(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    // 查询前缀和 up to idx
    int query(int idx) const {
        int result = 0;
        int x = idx;
        while (x > 0) {
            result += tree[x];
            x -= x & -x;
        }
        return result;
    }

    // 查询范围和 [l, r]
    int query(int l, int r) const {
        return query(r) - query(l - 1);
    }
};

// 线段树实现
class SegmentTree {
public:
    vector<int> tree;
    int n;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        build(1, 1, n);
    }

    // 构建树
    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = 1;  // 初始化为1（未使用）
        } else {
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    // 更新：将 idx 标记为已使用（设置为0）
    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node] = 0;
        } else {
            int mid = (l + r) / 2;
            if (idx <= mid) {
                update(node * 2, l, mid, idx);
            } else {
                update(node * 2 + 1, mid + 1, r, idx);
            }
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    // 查询第 k 个未使用的数字
    int query_kth(int node, int l, int r, int k) const {
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        if (tree[node * 2] >= k) {
            return query_kth(node * 2, l, mid, k);
        } else {
            return query_kth(node * 2 + 1, mid + 1, r, k - tree[node * 2]);
        }
    }
};

// 将排列转换为阶乘进制表示
vector<int> permutationToFactorial(const vector<int>& perm, int n) {
    vector<int> factorial_digits(n, 0);
    FenwickTree bit(n);
    for (int i = 1; i <= n; i++) {
        bit.update(i, 1);
    }

    for (int i = 0; i < n; i++) {
        int x = perm[i];
        factorial_digits[i] = bit.query(x - 1);
        bit.update(x, -1);
    }
    return factorial_digits;
}

// 将阶乘进制表示转换为排列
vector<int> factorialToPermutation(const vector<int>& factorial_digits, int n) {
    vector<int> perm;
    SegmentTree segTree(n);
    for (int i = 0; i < n; i++) {
        int k = factorial_digits[i] + 1;  // 1-based index
        int num = segTree.query_kth(1, 1, n, k);
        perm.push_back(num);
        segTree.update(1, 1, n, num);
    }
    return perm;
}

// 获取给定排列后的第 m 个排列
vector<int> getNextMPermutation(const vector<int>& perm, long long m, int n) {
    // 将当前排列转换为阶乘进制
    vector<int> factorial_digits = permutationToFactorial(perm, n);

    // 加上 m，处理进位
    long long carry = m;
    for (int i = n - 1, j = 1; i >= 0 && carry; i--, ++j) {
        long long temp = factorial_digits[i] + carry;
        factorial_digits[i] = temp % j;
        carry = temp / j;
    }

    // 将更新后的阶乘进制转换回排列
    vector<int> next_perm = factorialToPermutation(factorial_digits, n);
    return next_perm;
}

// 主函数示例
int main() {
    // 预计算阶乘
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 示例：当前排列 [2, 1, 3]
    int n;
    long long m;
    cin >> n >> m;
    
    vector<int> perm(n);
    for (int i = 0; i < n; ++i) 
        cin >> perm[i];

    // 获取后第 m 个排列
    vector<int> next_perm = getNextMPermutation(perm, m, n);

    for (int i = 0; i < n; ++i) {
        if (i < n-1) cout << next_perm[i] << ' ';
        else cout << next_perm[i] << '\n';
    }

    return 0;
}
