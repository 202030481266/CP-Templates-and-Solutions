#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;

static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> edges(2);
    for (int i = 0, u, v, t; i < m; ++i) {
        cin >> u >> v >> t;
        edges[t].emplace_back(v, u);
    }
    vector<vector<pii>> g(n + 1);
    ranges::sort(edges[0]);
    ranges::sort(edges[1]);
    for (int t = 0; t < 2; ++t) {
        int p = 0, sz = edges[t].size();
        while (p < sz) {
            int i = p + 1;
            while (i < sz && edges[t][i] == edges[t][p]) ++i;
            int u = edges[t][p].first, v = edges[t][p].second;
            g[u].emplace_back(v, t);
            p = i;
        }
    }
    vii dp(n + 1, vi(2, INF));
    dp[n][0] = dp[n][1] = 0;
    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int d = max(dp[u][0], dp[u][1]);
        for (auto [v, w] : g[u]) {
            if (dp[v][w] > d + 1 && v != u) {
                dp[v][w] = d + 1;
                if (dp[v][w ^ 1] < INF) q.push(v);
            }
        }
    }
    int d = max(dp[1][0], dp[1][1]);
    cout << (d == INF ? -1 : d) << '\n';
    for (int i = 1; i <= n; ++i) {
        if (dp[i][0] > dp[i][1]) cout << '0';
        else cout << '1';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
