#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

const int N = 100005;
vector<int> g[N];
int n, m, d, dep[N], d1[N], d2[N], monster[N];
int ans;

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    if (monster[u]) d1[u] = dep[u];
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            if (d1[v] > d1[u]) {
                d2[u] = d1[u];
                d1[u] = d1[v];
            }
            else if (d1[v] > d2[u]) d2[u] = d1[v];
        }
    }
}

void cal(int u, int fa, int dis) {
    if (dis > d) return; // its substree is impossible
    if (d1[u] - dep[u] <= d) ++ans;
    for (int v : g[u]) {
        if (v != fa) {
            if (dis == 0) {
                if (d1[v] == d1[u]) {
                    if (d2[u] == 0) cal(v, u, 0);
                    else cal(v, u, d2[u] - dep[u] + 1);
                }
                else {
                    if (d1[u] == 0) cal(v, u, 0);
                    else cal(v, u, d1[u] - dep[u] + 1);
                }
            }
            else {
                if (d1[v] == d1[u]) {
                    if (d2[u] == 0) cal(v, u, dis + 1);
                    else cal(v, u, max(dis, d2[u] - dep[u]) + 1);
                }
                else {
                    if (d1[u] == 0) cal(v, u, dis + 1);
                    else cal(v, u, max(dis, d1[u] - dep[u]) + 1);
                }
            }
        }
    }
}

void solve() {
    cin >> n >> m >> d;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        monster[x] = 1;
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cal(1, 0, 0);
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
