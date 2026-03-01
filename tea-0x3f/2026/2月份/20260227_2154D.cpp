// Problem: D. Catshock
// Contest: Codeforces - Codeforces Round 1060 (Div. 2)
// URL: https://codeforces.com/problemset/problem/2154/D
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
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vii g(n + 1);
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vi dep(n + 1);
    vi father(n + 1);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        father[u] = fa;
        for (int v : g[u]) {
            if (v != fa) {
                dep[v] = dep[u] + 1;
                self(self, v, u);
            }
        }
    };
    dfs(dfs, 1, 0);
    vi path;
    vi need(n + 1);
    int cur = n;
    while (cur) {
        path.push_back(cur);
        cur = father[cur];
    }
    for (int v : path) need[v] = 1;
    reverse(path.begin(), path.end());
    int flag = 0;
    vi b;
    vi d(n + 1);
    for (int i = 1; i <= n; ++i) {
        d[i] = i == 1 ? g[1].size() : g[i].size() - 1;
        if (d[i] == 0 && !need[i]) b.push_back(i);
    }
    vector<string> ans;
    while (!b.empty()) {
        vi nxt;
        for (int u : b) {
            int x = dep[u] & 1;
            if (x ^ flag) {
                ans.push_back("2 " + to_string(u));
                ans.push_back("1");
                flag ^= 1;
            }
            else {
                ans.push_back("1");
                ans.push_back("2 " + to_string(u));
                ans.push_back("1");
            }
            if (father[u] && !need[father[u]]) {
                --d[father[u]];
                if (d[father[u]] == 0) {
                    nxt.push_back(father[u]);
                }
            }
        }
        b = move(nxt);
    }
    for (int i = 0; i < path.size() - 1; ++i) {
        int x = i & 1;
        if (x ^ flag) {
            ans.push_back("2 " + to_string(path[i]));
            ans.push_back("1");
            flag ^= 1;
        }
        else {
            ans.push_back("1");
            ans.push_back("2 " + to_string(path[i]));
            ans.push_back("1");
        }
    }
    cout << ans.size() << '\n';
    for (const string& s : ans) {
        cout << s << '\n';
    }
    cout << '\n';
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