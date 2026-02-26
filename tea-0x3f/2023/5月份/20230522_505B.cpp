// Problem: B. Mr. Kitayuta's Colorful Graph
// Contest: Codeforces - Codeforces Round 286 (Div. 2)
// URL: https://codeforces.com/problemset/problem/505/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int fa[102][102];

int find(int c, int x) {
    return fa[c][x] == x ? x : fa[c][x] = find(c, fa[c][x]);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) fa[i][j] = j;
    }
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c;
        int fu = find(c, u);
        int fv = find(c, v);
        fa[c][fu] = fv;
    }
    int q;
    cin >> q;
    for (int i = 0, u, v; i < q; ++i) {
        cin >> u >> v;
        int ans = 0;
        for (int j = 1; j <= m; ++j) {
            if (find(j, u) == find(j, v)) ++ans;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}