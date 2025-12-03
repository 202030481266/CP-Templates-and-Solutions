// https://codeforces.com/problemset/problem/2081/A
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int mod = 1e9 + 7;
static constexpr int maxn = 100007;

int n;
string num;

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

ll dp[maxn][2], inv;

void solve() {
    cin >> n >> num;
    memset(dp, 0, sizeof(dp));
    vector<int> lone(n), lzero(n);  
    int pone = -1, pzero = -1;
    for (int i = 0; i < n; ++i) {
        lone[i] = pone;
        lzero[i] = pzero;
        if (num[i] == '0') pzero = i;
        else pone = i;
    }
    for (int i = 1; i < n; ++i) {
        if (lzero[i] == -1) {
            dp[i][1] = (dp[i][1] + (i + 1) * inv % mod) % mod;
            if (num[i-1] == '1') {
                dp[i][1] = (dp[i][1] + (dp[i-1][1] + 1) * inv % mod) % mod;
            }
            else {
                dp[i][1] = (dp[i][1] + (dp[i-1][0] + 1) * inv % mod) % mod;
            }
        }
        else {
            dp[i][1] = (dp[i][1] + (dp[lzero[i]][1] + i - lzero[i]) * inv % mod) % mod;
            if (num[i-1] == '1') {
                dp[i][1] = (dp[i][1] + (dp[i-1][1] + 1) * inv % mod) % mod;
            }
            else {
                dp[i][1] = (dp[i][1] + (dp[i-1][0] + 1) * inv % mod) % mod;
            }
        }
        dp[i][0] = (dp[lone[i]][1] + i - lone[i]) % mod;
    }
    cout << dp[n-1][num[n-1]-'0'] << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    inv = quick_pow(2, mod - 2);
    while (t--) solve();
}