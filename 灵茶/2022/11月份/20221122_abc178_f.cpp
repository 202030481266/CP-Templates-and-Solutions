// Problem: F - Contrast
// Contest: AtCoder - AtCoder Beginner Contest 178
// URL: https://atcoder.jp/contests/abc178/tasks/abc178_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int> >;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    vi same;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) same.push_back(i);
    }
    int p = 0, mx = 0, idx = 0;
    while (p < same.size()) {
        int i = p + 1;
        while (i < same.size() && a[same[i]] == a[same[p]]) ++i;
        if (i - p > mx) {
            mx = i - p;
            idx = p;
        }
        p = i;
    }
    if (mx > same.size() - mx) {
        int m = same.size(), need = 2 * mx - m;
        for (int i = 0; i < n && need; ++i) {
            if (a[i] != b[i] && a[i] != a[same[idx]] && b[i] != b[same[idx]]) {
                same.push_back(i);
                --need;
            }
        }
        if (need > 0) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    // 循环位移
    int offset = mx, m = same.size();
    vi pre = same;
    vi vis(m);
    for (int i = 0; i < m; ++i) {
        int cur = i, val = same[i];
        while (!vis[cur]) {
            vis[cur] = 1;
            int nxt = (cur + offset) % m;
            int tmp = same[nxt];
            same[nxt] = val;
            val = tmp;
            cur = nxt;
        }
    }
    vi ids(n);
    iota(ids.begin(), ids.end(), 0);
    for (int i = 0; i < m; ++i) ids[pre[i]] = same[i];
    for (int i = 0; i < n; ++i) cout << b[ids[i]] << ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
