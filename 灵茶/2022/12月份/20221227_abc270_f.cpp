// Problem: F - Transportation
// Contest: AtCoder - TOYOTA MOTOR CORPORATION Programming Contest 2022(AtCoder Beginner Contest 270)
// URL: https://atcoder.jp/contests/abc270/tasks/abc270_f
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int> >;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 500005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n, m;
    cin >> n >> m;
    vl a(n), b(n);
    vector<array<int, 3>> e(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < m; ++i) {
        cin >> e[i][1] >> e[i][2] >> e[i][0];
        --e[i][1];
        --e[i][2];
    }
    ranges::sort(e);
    vl d(n);
    vi fa(n);
    for (int i = 0; i < n; ++i) d[i] = min(a[i], b[i]);
    auto find = [&](int x) -> int {
        int root = x;
        while (fa[root] != root) root = fa[root];
        while (x != fa[x]) {
            int nxt = fa[x];
            fa[x] = root;
            x = nxt;
        }
        return root;
    };
    auto cal = [&](const vl& w) -> ll {
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
            sum += w[i];
        }
        for (int i = 0; i < m; ++i) {
            int u = e[i][1], v = e[i][2], c = e[i][0];
            int fu = find(u);
            int fv = find(v);
            if (fu != fv && c <= max(w[fu], w[fv])) {
                sum += c - max(w[fu], w[fv]);
                if (w[fu] > w[fv]) swap(fu, fv);
                fa[fv] = fu;
            }
        }
        return sum;
    };
    ll ans = min(cal(a), cal(b));
    ll res = cal(d);
    vl mn_a(n, LLINF);
    vl mn_b(n, LLINF);
    for (int i = 0; i < n; ++i) {
        int f = find(i);
        mn_a[f] = min(mn_a[f], a[i]);
        mn_b[f] = min(mn_b[f], b[i]);
    }
    for (int i = 0; i < n; ++i) {
        if (find(i) == i) {
            ans = min(ans, res - d[i] + mn_a[i] + mn_b[i]);
        }
    }
    for (int i = 0; i < m; ++i) { // 这可以通过贪心证明
        int u = e[i][1], v = e[i][2], c = e[i][0];
        int fu = find(u);
        int fv = find(v);
        if (fu != fv) {
            ll ma = min(mn_a[fu], mn_a[fv]);
            ll mb = min(mn_b[fu], mn_b[fv]);
            ll cost = res - d[fu] - d[fv] + ma + mb + c;
            ans = min(ans, cost);
        }
    }
    int merge = 0;
    ll krus = 0;
    for (int i = 0; i < n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        int u = e[i][1], v = e[i][2], c = e[i][0];
        int fu = find(u);
        int fv = find(v);
        if (fu != fv) {
            fa[fu] = fv;
            ++merge;
            krus += c;
        }
    }
    if (merge == n - 1) ans = min(ans, krus);
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}