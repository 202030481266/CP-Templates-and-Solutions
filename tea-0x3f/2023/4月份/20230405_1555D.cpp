// Problem: D. Say No to Palindromes
// Contest: Codeforces - Educational Codeforces Round 112 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1555/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vi s(n + 1);
    char ch;
    for (int i = 1; i <= n; ++i) {
        cin >> ch;
        s[i] = ch - 'a';
    }
    // abc, acb, bac, bca, cab, cba
    vi a{0, 1, 2};
    vii sum(6, vi(n + 1));
    int p = 0;
    do {
        for (int i = 1, j = 0; i <= n; ++i, j = (j + 1) % 3) {
            sum[p][i] = sum[p][i - 1] + (s[i] != a[j] ? 1 : 0);
        }
        ++p;
    } while (next_permutation(a.begin(), a.end()));
    while (m--) {
        int l, r;
        cin >> l >> r;
        int ans = INF;
        for (int i = 0; i < 6; ++i) ans = min(ans, sum[i][r] - sum[i][l - 1]);
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}