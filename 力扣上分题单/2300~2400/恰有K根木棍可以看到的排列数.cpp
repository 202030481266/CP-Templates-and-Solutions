// https://leetcode.cn/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/



typedef long long ll;
ll fac[1010], ifac[1010];
class Solution {
	static constexpr int mod = 1000000007;
	ll quick_power(ll a, ll b) {
		ll res = 1;
		for (; b; b >>= 1) {
			if (b & 1) res = res * a % mod;
			a = a * a % mod;
		}
		return res;
	}
	ll inv(ll x) {
		return quick_power(x, mod - 2);
	}
	ll C(ll x, ll y) {
		return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
	}
public:
    int rearrangeSticks(int n, int k) {
    	ll dp[n + 1][k + 1];
    	memset(dp, 0, sizeof(dp));
    	fac[0] = 1;
    	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    	ifac[n] = inv(fac[n]);
    	for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    	dp[0][0] = 1;
    	for (int i = 1; i <= k; ++i) 
    		for (int j = i; j <= n; ++j) 
    			for (int x = i; x <= j; ++x)
    				dp[j][i] = (dp[j][i] + C(j - 1, x - 1) * (dp[x - 1][i - 1] * fac[j - x] % mod) % mod) % mod;
    	return dp[n][k];
    }
};



typedef long long ll;
ll fac[1010], ifac[1010];
class Solution {
	static constexpr int mod = 1000000007;
	ll quick_power(ll a, ll b) {
		ll res = 1;
		for (; b; b >>= 1) {
			if (b & 1) res = res * a % mod;
			a = a * a % mod;
		}
		return res;
	}
	ll inv(ll x) {
		return quick_power(x, mod - 2);
	}
public:
    int rearrangeSticks(int n, int k) {
    	ll dp[n + 1][k + 1], g[n + 1][k + 1];
    	memset(dp, 0, sizeof(dp));
    	memset(g, 0, sizeof(g));
    	fac[0] = 1;
    	for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    	ifac[n] = inv(fac[n]);
    	for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    	dp[0][0] = g[0][0] = 1;
    	for (int i = 1; i <= n; ++i) g[i][0] = (g[i - 1][0] + dp[i][0] * ifac[i] % mod) % mod;
    	for (int i = 1; i <= k; ++i) {
    		for (int j = i; j <= n; ++j) {
    			if (i - 2 < 0)
    				dp[j][i] = (fac[j - 1] * g[j - 1][i - 1]) % mod;
    			else dp[j][i] = (fac[j - 1] * ((g[j - 1][i - 1] - g[i - 2][i - 1] + mod) % mod)) % mod;
    		}
    		for (int j = i; j <= n; ++j) g[j][i] = ifac[j] * dp[j][i] % mod;
    		for (int j = i + 1; j <= n; ++j) g[j][i] = (g[j][i] + g[j - 1][i]) % mod;
    	}
    	return dp[n][k];
    }
};