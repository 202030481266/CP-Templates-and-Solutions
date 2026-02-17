// Problem: B. Tree Tag
// Contest: Codeforces - Codeforces Round 668 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1404/B
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

int getTreeDiameter(int n, const vector<vector<int>>& g) {
    if (n <= 1) return 0;
    auto dfs = [&](auto self, int u, int p, int dist) -> pair<int, int> {
        pair<int, int> res = {dist, u};
        for (int v : g[u]) {
            if (v != p) {
                res = max(res, self(self, v, u, dist + 1));
            }
        }
        return res;
    };
    pair<int, int> p1 = dfs(dfs, 1, 0, 0);
    pair<int, int> p2 = dfs(dfs, p1.second, 0, 0);
    return p2.first;
}

void solve() {
    int n, a, b, na, nb;
    cin >> n >> a >> b >> na >> nb;
    vii g(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (nb <= 2 * na) {
        cout << "Alice\n";
        return;
    }
    vi dis(n + 1);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        dis[u] = dis[fa] + 1;
        for (int v : g[u]) {
            if (v != fa) self(self, v, u);
        }
    };
    dfs(dfs, b, 0);
    if (dis[a] - dis[b] <= na) {
        cout << "Alice\n";
        return;
    }
    int dia = getTreeDiameter(n, g);
    if (dia > 2 * na) cout << "Bob\n";
    else cout << "Alice\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}