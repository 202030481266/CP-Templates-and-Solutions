// https://codeforces.com/problemset/problem/1670/F
// 很好的逆向思维题目
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int mod = 1e9 + 7;
static constexpr int maxv = 64 * 1000;
static constexpr int maxn = 70000;

long long fac[maxn], ifac[maxn];

long long quick_power(long long a, long long b, int p) { 
    long long ans = 1 % p;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}

long long inv(long long x, int p = mod) {
	return quick_power(x, p - 2, p) % mod;
}

long long binomial(int x, int y) {
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

void init() {
    int n = maxv;
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

ll l, r, z;
int n;
ll dp[64][maxv];

ll dfs_timeout(ll x, int pos, int ones) {
    if (pos < 0) return 1;
    if (dp[pos][ones] != -1) return dp[pos][ones];
    ll& res = dp[pos][ones];
    res = 0;
    ones += ((x >> pos) & 1);
    if (ones == 0 && ((z >> pos) & 1)) return res;
    for (int i = (z >> pos) & 1; i <= min(n, ones); i += 2) {
        // 这里从高位枚举到低位，导致状态为O(w*n)
        res = (res + binomial(n, i) * dfs(x, pos - 1, min((ones - i) * 2, pos * n)) % mod) % mod; // (pos, 0]
    }
    return res;
}

ll dfs(ll x, int use, int pos) {
    if (pos >= 64) return use == 0;
    if (dp[pos][use] != -1) return dp[pos][use];
    ll& res = dp[pos][use];
    res = 0;
    for (int i = (z >> pos) & 1; i <= n; i += 2) {
        // 从低位枚举到高位能够将状态压缩到 O(n) 而不是 O(w*n)，属于逆向思维的想法
        res = (res + binomial(n, i) * dfs(x, (use + i - ((x >> pos) & 1) + 1) >> 1, pos + 1) % mod) % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    init();    
    cin >> n >> l >> r >> z;
    memset(dp, -1, sizeof(dp));    
    ll res_l = dfs(l - 1, 0, 0);
    memset(dp, -1, sizeof(dp));
    ll res_r = dfs(r, 0, 0);
    cout << (res_r - res_l + mod) % mod << endl;
}