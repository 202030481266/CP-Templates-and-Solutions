#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200005;

int n, m, vis[MAXN][2], can[MAXN][2];
ll k, a[MAXN], d[MAXN];
ll f[MAXN], g[MAXN];
pair<ll, int> ff[MAXN];
pair<ll, int> gg[MAXN];

int find_right(int p, ll val) { // 找到 p 右边第一个 val 的位置
    if (p > n) return -1;
    auto pos = static_cast<int>(lower_bound(ff + 1, ff + 1 + n, make_pair(val, p + 1)) - ff);
    return pos <= n && ff[pos].first == val ? ff[pos].second : -1;
}

int find_left(int p, ll val) { // 找到 p 左边最后一个 val 的位置
    if (p > n) return -1;
    auto pos = static_cast<int>(lower_bound(gg + 1, gg + 1 + n, make_pair(val, p)) - gg);
    return pos > 1 && gg[pos - 1].first == val ? gg[pos - 1].second : -1;
}

void walk(int p, int dir) {
    vector<pair<int, int>> tmp;
    int nxt = -1;
    while (!vis[p][dir]) {
        tmp.emplace_back(p, dir);
        vis[p][dir] = 1;
        if (!dir) nxt = find_right(p, f[p]);
        else nxt = find_left(p, g[p]);
        if (nxt == -1) {
            for (auto [key, val] : tmp) { // can walk outside
                can[key][val] = 1;
            }
            break;
        }
        p = nxt;
        dir ^= 1;
    }
    if (nxt != -1) {
        // can[p][dir] is already known
        for (auto [key, val] : tmp) {
            can[key][val] = can[p][dir];
        }
    }
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) {
        f[i] = ((a[i] - d[i]) % k + k) % k;
        g[i] = (a[i] + d[i]) % k;
        ff[i] = {f[i], i};
        gg[i] = {g[i], i};
    }
    sort(ff + 1, ff + 1 + n);
    sort(gg + 1, gg + 1 + n);
    for (int i = 1; i <= n; ++i) vis[i][0] = vis[i][1] = 0;
    for (int i = 1; i <= n; ++i) can[i][0] = can[i][1] = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i][0]) walk(i, 0);
        if (!vis[i][1]) walk(i, 1);
    }
    cin >> m;
    ll v;
    for (int i = 1; i <= m; ++i) {
        cin >> v;
        auto it = static_cast<int>(lower_bound(a + 1, a + 1 + n, v) - a);
        if (it <= n) {
            if (a[it] == v && d[it] == 0) {
                if (can[it][1]) cout << "YES\n";
                else cout << "NO\n";
            }
            else {
                int p = find_right(it - 1, v % k);
                if (p == -1 || can[p][1]) cout << "YES\n";
                else cout << "NO\n";
            }
        }
        else cout << "YES\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}