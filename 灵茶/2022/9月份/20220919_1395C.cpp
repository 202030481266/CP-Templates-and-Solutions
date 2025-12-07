// Problem: C. Boboniu and Bit Operations
// Contest: Codeforces - Codeforces Round 664 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1395/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;

int n, m, a[300], b[300];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    // 高级解法
    int ans = 0;
    for (int i = 8; i >= 0; --i) {
        int zero = 1;
        for (int j = 1; j <= n; ++j) {
            int flag = 0;
            for (int k = 1; k <= m; ++k) {
                if (((a[j] & b[k]) >> i) == 0) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                zero = 0;
                break;
            }
        }
        if (!zero) {
            for (int j = 1; j <= n; ++j) a[j] &= ~(1 << i);
            ans |= 1 << i;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
