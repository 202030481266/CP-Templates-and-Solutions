#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

int n, m;
int val[MAXN];

const int N = 1e5 + 9, LG = 18;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];

void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    if (p) {
        auto it = find(g[u].begin(), g[u].end(), p);
        if (it != g[u].end()) {
            swap(*it, g[u].back());
            g[u].pop_back();
        }
    }

    for (auto& v : g[u]) {
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}

int T, head[N], st[N], en[N];

void dfs_hld(int u) {
    st[u] = ++T;
    for (auto v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v);
    }
    en[u] = T;
}

int rk[MAXN];

struct Q {
    int u, v, x, rnk;
} qs[MAXN];

ll ans[MAXN];
int sum[MAXN][32];
ll con[MAXN][32];

vector<int> get_primes(int n) {
    if (n <= 1) return {};
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= n; i++)
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;

    vector<int> primes;
    for (int i = 0; i < prime.size(); ++i)
        if (prime[i]) primes.push_back(i);
    return primes;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}

void solve() {
    if (!(cin >> n)) return;
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    head[1] = 1;
    dfs_hld(1);
    
    int mx_val = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        if (val[i] > mx_val) mx_val = val[i];
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> qs[i].u >> qs[i].v >> qs[i].x;
        if (qs[i].x > mx_val) mx_val = qs[i].x;
        qs[i].rnk = 0;
        ans[i] = 1;
    }
    
    auto primes = get_primes(sqrt(mx_val));
    vector g1(primes.size(), vector<pii>{});
    vector g2(primes.size(), vector<pii>{});
    vi mx(primes.size(), 0);
    
    for (size_t j = 0; j < primes.size(); ++j) {
        for (int i = 1; i <= n; ++i) {
            int c = 0;
            while (val[i] % primes[j] == 0) {
                ++c;
                val[i] /= primes[j];
            }
            if (c) {
                g1[j].emplace_back(st[i], c);
                if (c > mx[j]) mx[j] = c;
            }
        }
    }
    for (size_t j = 0; j < primes.size(); ++j) {
        for (int i = 1; i <= m; ++i) {
            int c = 0;
            while (qs[i].x % primes[j] == 0) {
                ++c;
                qs[i].x /= primes[j];
            }
            if (c) {
                g2[j].emplace_back(i, c);
                if (c > mx[j]) mx[j] = c;
            }
        }
    }
    
    auto fun = [&](int l, int r, int qc, int j) -> int {
        int ql = lower_bound(g1[j].begin(), g1[j].end(), make_pair(l, 0)) - g1[j].begin();
        int qr = upper_bound(g1[j].begin(), g1[j].end(), make_pair(r, INF)) - g1[j].begin();
        int have = 0;
        if (qr > ql) {
            int len = qr - ql;
            int big = len - (sum[qr][qc] - sum[ql][qc]);
            have = con[qr][qc] - con[ql][qc] + big * qc;
        }
        return have;
    };
    
    for (size_t j = 0; j < primes.size(); ++j) {
        if (g1[j].empty() || g2[j].empty()) continue;
        sort(g1[j].begin(), g1[j].end());
        int nn = g1[j].size();
        for (int i = 0; i < nn; ++i) {
            for (int k = 1; k <= mx[j]; ++k) sum[i + 1][k] = sum[i][k] + (g1[j][i].second == k ? 1 : 0);
        }
        for (int i = 1; i <= nn; ++i) {
            for (int k = 1; k <= mx[j]; ++k) {
                con[i][k] = sum[i][k] * k + con[i][k - 1];
                sum[i][k] += sum[i][k - 1];
            }
        }
        for (auto [qid, qc] : g2[j]) {
            int u = qs[qid].u, v = qs[qid].v, qcnt = 0;
            while (head[u] != head[v]) {
                if (dep[head[u]] < dep[head[v]]) swap(u, v);
                qcnt += fun(st[head[u]], st[u], qc, j);
                u = par[head[u]][0];
            }
            if (dep[u] < dep[v]) swap(u, v);
            qcnt += fun(st[v], st[u], qc, j); 
            ans[qid] = ans[qid] * quick_pow(primes[j], qcnt) % MOD;
        }
        for (int i = 1; i <= nn; ++i) {
            for (int k = 1; k <= mx[j]; ++k) {
                con[i][k] = sum[i][k] = 0;
            }
        }
    }
    // HLD 处理剩余的大质数（或 1）
    vector<pii> b;
    for (int i = 1; i <= n; ++i) {
        if (val[i] > 1) b.emplace_back(val[i], i);
    }
    for (int i = 1; i <= m; ++i) {
        if (qs[i].x > 1) b.emplace_back(qs[i].x, n + i);
    }
    sort(b.begin(), b.end());
    int cur = 0;
    for (size_t i = 0; i < b.size(); ++i) {
        if (i == 0 || b[i].first != b[i - 1].first) ++cur;
        if (b[i].second <= n) rk[b[i].second] = cur;
        else qs[b[i].second - n].rnk = cur;
    }
    vii dfn(cur + 1);
    for (int i = 1; i <= n; ++i) {
        dfn[rk[i]].push_back(st[i]);
    }
    for (int i = 1; i <= cur; ++i) sort(dfn[i].begin(), dfn[i].end());
    
    auto cal = [&](int l, int r, int v) -> int {
        int ql = lower_bound(dfn[v].begin(), dfn[v].end(), l) - dfn[v].begin();
        int qr = upper_bound(dfn[v].begin(), dfn[v].end(), r) - dfn[v].begin();
        return qr - ql;
    };
    
    auto up = [&](int u, int v, int rnk) -> int {
        int cnt = 0;
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            cnt += cal(st[head[u]], st[u], rnk);
            u = par[head[u]][0];
        }
        if (dep[u] < dep[v]) swap(u, v);
        cnt += cal(st[v], st[u], rnk);
        return cnt;
    };
    
    for (int i = 1; i <= m; ++i) {
        if (qs[i].rnk == 0) continue;
        int u = qs[i].u, v = qs[i].v, rnk = qs[i].rnk;
        int cnt = up(u, v, rnk); // 2个log
        ans[i] = ans[i] * quick_pow(qs[i].x, cnt) % MOD; // 1个log
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}