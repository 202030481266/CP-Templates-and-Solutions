// Problem: B. Zero Tree
// Contest: Codeforces - Codeforces Round 168 (Div. 1)
// URL: https://codeforces.com/problemset/problem/274/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n;    
    cin >> n;
    vii g(n + 1);
    vector<ll> arr(n + 1), add(n + 1), sub(n + 1);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        for (int v : g[u]) {
            if (v != fa) {
                self(self, v, u);
                add[u] = max(add[u], add[v]);
                sub[u] = max(sub[u], sub[v]);
            }
        }
        arr[u] += add[u] - sub[u];
        if (arr[u] > 0) sub[u] += arr[u];
        else add[u] += -arr[u];
    };
    dfs(dfs, 1, 0);
    cout << add[1] + sub[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}