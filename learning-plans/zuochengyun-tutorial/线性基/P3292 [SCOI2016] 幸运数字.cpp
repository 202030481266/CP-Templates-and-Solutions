#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 20003;
const int L = 15;
int n, q, up[maxn][L], dep[maxn];
ll val[maxn];
ll b[maxn][L][61]; // b[i][j][k] 表示 [i,up[i][j]] 的 k 位置上的线性基
vector<int> g[maxn];

// 树上倍增 + LCA + 异或线性基
void update(int u, int d, ll value) {
    for (int i = 60; i >= 0 && value; --i) {
        if (value & (1ll << i)) {
            if (b[u][d][i]) value ^= b[u][d][i];
            else {
                b[u][d][i] = value;
                break;
            }
        }
    }
}
void dfs(int u, int fa) {
    up[u][0] = fa;
    dep[u] = dep[fa] + 1;
    update(u, 0, val[u]);
    update(u, 0, val[fa]);
    for (int i = 1; i < L; ++i) {
        up[u][i] = up[up[u][i-1]][i-1];
        // for (int j = 0; j < 61; ++j) 
        //     b[u][i][j] = b[u][i-1][j];
        memcpy(b[u][i], b[u][i-1], sizeof(ll) * 61);
        for (int k = 60; k >= 0; --k) { // 枚举 b[up[u][i-1]][i-1] 中的线性基
            if (b[up[u][i-1]][i-1][k]) {
                update(u, i, b[up[u][i-1]][i-1][k]);
            }
        }
    }
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u);
        }
    }
}
ll ans[61];
void update_ans(int u, int k) {
    for (int p = 60; p >= 0; --p) {
        if (b[u][k][p]) {
            ll value = b[u][k][p];
            for (int i = p; i >= 0 && value; --i) {
                if (value & (1ll << i)) {
                    if (ans[i]) value ^= ans[i];
                    else {
                        ans[i] = value;
                        break;
                    }
                }
            }
        }
    }
}
void lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = L-1; k >= 0; --k) {
        if (dep[up[u][k]] >= dep[v]) {
            // [u, up[u][k]]
            update_ans(u, k);
            u = up[u][k];
        }
    }
    if (u == v) return;
    for (int k = L-1; k >= 0; --k) {
        if (up[u][k] != up[v][k]) {
            // [u, up[u][k]], [v, up[v][k]]
            update_ans(u, k);
            update_ans(v, k);
            u = up[u][k];
            v = up[v][k];
        }
    }
    update_ans(v, 0);
    update_ans(u, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    int x, y;
    ll res;
    for (int i = 0; i < q; ++i) {
        cin >> x >> y;
        if (x == y) {
        	cout << val[x] << '\n';
        	continue;
        }
        memset(ans, 0, sizeof(ans));
        lca(x, y);
        res = 0;
        for (int i = 60; i >= 0; --i) res = max(res, res ^ ans[i]);
        cout << res << '\n';
    }
    return 0;
}