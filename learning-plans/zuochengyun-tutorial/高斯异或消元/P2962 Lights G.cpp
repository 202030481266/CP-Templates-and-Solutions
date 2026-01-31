// https://www.luogu.com.cn/problem/P2962
// 相当经典和有趣的一道题目，做法可以使用动态规划(状态压缩)，也可以使用高斯消元法

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 40;
int g[maxn][maxn];
int val[maxn], ans, n, m;


// 如果一个主元依赖于其他的自由元，那么最后的方程表达中，该自由元一定在主元的下面
void dfs(int p, int res) {
    if (res >= ans) return;
    if (p < 0) {
        ans = res;
        return;
    }
    if (!g[p][p]) {
        val[p] = 0;
        dfs(p-1, res);
        val[p] = 1;
        dfs(p-1, res+1);
    }
    else {
        // x ^ f1 ^ f2 ^ f3... = g[x][n]
        // x = g[x][n] ^ f1 ^ f2 ^ f3 ...
        int c = g[p][n];
        for (int j = p+1; j < n; ++j) {
            if (g[p][j]) {
                c ^= val[j];
            }
        }
        dfs(p-1, res+c);
    }
}
void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        g[i][i] = 1;
        g[i][n] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x-1][y-1] = g[y-1][x-1] = 1; // 0-index
    }
    // 异或主要解决奇偶性问题
    // gauss
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j < i && g[j][j]) continue;
            if (g[j][i]) {
                swap(g[i], g[j]);
                break;
            }
        }
        if (!g[i][i]) continue; // 自由元
        for (int j = 0; j < n; ++j) {
            if (j != i && g[j][i]) {
                for (int k = i; k <= n; ++k) {
                    g[j][k] ^= g[i][k];
                }
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        if (!g[i][i]) {
            flag = false;
            break;
        }
        ans += g[i][n];
    }
    if (!flag) {
        ans = n; // 至少所有选取一次 ，可以证明所有的元素最多被选一次
        dfs(n-1, 0);
    }
    cout << ans << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}