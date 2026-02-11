// Problem: C. Binary Search
// Contest: Codeforces - Codeforces Round 678 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1436/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
    int n, x, pos;
    cin >> n >> x >> pos;
    int l = 0, r = n;
    int great = 0, less = 0;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (mid > pos) ++great;
        if (mid < pos) ++less;
        if (mid <= pos) l = mid + 1;
        else r = mid;
    }
    // (x, n], [1, x)
    if (n - x < great || x - 1 < less) {
        cout << 0 << '\n';
        return;
    }
    // C(n-x,great)*fac(great)*C(x-1,less)*fac(less)*fac(n-1-great-less)
    vii C(n + 1, vi(n + 1));
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
    vi fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = 1LL * fac[i - 1] * i % MOD;
    int ac = 1ll * C[n - x][great] * C[x - 1][less] % MOD;
    int af = 1ll * fac[great] * fac[less] % MOD * fac[n - 1 - great - less] % MOD;
    cout << (1ll * ac * af % MOD) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}