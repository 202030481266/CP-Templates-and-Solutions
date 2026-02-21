// Problem: F. Imbalance Value of a Tree
// Contest: Codeforces - Educational Codeforces Round 36 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/915/F
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

void solve() {
    int n;
    cin >> n;
    vi arr(n + 1);
    vii g(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi ids(n + 1);
    vi fa(n + 1);
    vi sz(n + 1);
    auto find = [&](auto&& self, int u) -> int {
        return fa[u] == u ? u : fa[u] = self(self, fa[u]);
    };
    auto init = [&]() -> void {
        iota(ids.begin(), ids.end(), 0);
        iota(fa.begin(), fa.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    };
    init();
    sort(ids.begin() + 1, ids.end(), [&](int i, int j){
        return arr[i] < arr[j];
    });
    ll ans = 0;
    int p = 1;
    while (p <= n) {
        int i = p + 1;
        while (i <= n && arr[ids[i]] == arr[ids[p]]) ++i;
        for (int j = p; j < i; ++j) {
            int u = ids[j];
            for (int v : g[u]) {
                if (arr[v] > arr[u]) continue;
                int fu = find(find, u);
                int fv = find(find, v);
                if (fu == fv) continue;
                ans += 1LL * sz[fv] * arr[u] * sz[fu];
                sz[fu] += sz[fv];
                fa[fv] = fu;
            }
        }
        p = i;
    }
    init();
    sort(ids.begin() + 1, ids.end(), [&](int i, int j){
        return arr[i] > arr[j];
    });
    p = 1;
    while (p <= n) {
        int i = p + 1;
        while (i <= n && arr[ids[i]] == arr[ids[p]]) ++i;
        for (int j = p; j < i; ++j) {
            int u = ids[j];
            for (int v : g[u]) {
                if (arr[v] < arr[u]) continue;
                int fu = find(find, u);
                int fv = find(find, v);
                if (fu == fv) continue;
                ans -= 1LL * sz[fv] * arr[u] * sz[fu];
                sz[fu] += sz[fv];
                fa[fv] = fu;
            }
        }
        p = i;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}