// Problem: C - Shuffle Permutation
// Contest: AtCoder - AtCoder Regular Contest 107
// URL: https://atcoder.jp/contests/arc107/tasks/arc107_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int> >;
static constexpr int MAXN = 500005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

#include <atcoder/modint.hpp>
using namespace atcoder;
using mint = modint998244353;

void solve() {
    int n, k;
    cin >> n >> k;
    vii r1(n, vi(n));
    vii r2(n, vi(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> r1[i][j];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) r2[i][j] = r1[j][i];
    }
    mint ans = 1;
    vector<mint> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * i;
    auto cal = [&](vii& row) -> void {
        dsu d(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int flag = 1;
                for (int x = 0; x < n; ++x) {
                    if (row[i][x] + row[j][x] > k) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) d.merge(i, j);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (d.leader(i) == i) {
                ans *= pw[d.size(i)];
            }
        }
    };
    cal(r1);
    cal(r2);
    cout << ans.val() << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
