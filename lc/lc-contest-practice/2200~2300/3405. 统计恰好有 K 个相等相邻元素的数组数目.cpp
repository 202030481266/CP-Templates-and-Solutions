#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int maxn = 100010;
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
	fac[0] = 1;
    int n = 100000; // 10^5
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

bool flag = false;

class Solution {
public:
    int countGoodArrays_dp(int n, int m, int k) {
        vector dp(n+1, vector<ll>(k+1));
        dp[0][0] = m;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] += dp[i-1][j]*(m-1)%mod;
                if (j > 0) dp[i][j] += dp[i-1][j-1];
                dp[i][j] %= mod;
            }
        }
        return dp[n-1][k];
    }
    int countGoodArrays(int n, int m, int k) {
        if (!flag) {
            flag = true;
            init();
        }
        ll res = binomial(n-1, k);
        ll tmp = 1;
        for (int i = 0; i < n-1-k; ++i) tmp = tmp*(m-1)%mod;
        res = res * (tmp * m % mod) % mod;
        return res;
    }
};