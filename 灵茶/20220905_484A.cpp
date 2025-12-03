// Problem: A. Bits
// Contest: Codeforces - Codeforces Round 276 (Div. 1)
// URL: https://codeforces.com/problemset/problem/484/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;


void solve() {
    ll L, R;
    cin >> L >> R;
    int w = bit_width(1ull * R);
    int limit = 1, cur = 0, ans = 0, idx = -1;
    for (int i = w - 1; i >= 0; --i) {
        int br = R >> i & 1, bl = L >> i & 1;
        if (br > bl && limit) limit = 0;
        if (br) {
            if (!limit) {
                if (ans < cur + i) {
                    ans = cur + i;
                    idx = i;
                }
            }
            ++cur;
        }
    }
    if (cur > ans) cout << R << '\n';
    else {
        if (ans == 0) cout << 0 << '\n';
        else cout << ((R >> idx + 1 << idx + 1) + (1ll << idx) - 1) << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
