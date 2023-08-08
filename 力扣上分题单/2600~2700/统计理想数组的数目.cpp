typedef long long ll;
class Solution {
    static constexpr int mod = 1e9 + 7;
    ll dp[10010][15], a[15], fac[10010], ifac[10010];
public:
    long long quick_power(long long a, long long b) {
        long long ans = 1 % mod;
        for (; b; b >>= 1) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
        }
        return ans;
    }
    long long inv(long long x) {
        return quick_power(x, mod - 2) % mod;
    }
    long long binomial(int x, int y) {
        return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
    }
    int idealArrays(int n, int maxValue) {
        for (int i = 1; i <= maxValue; ++i) dp[i][1] = 1;
        for (int i = 1; i <= min(13, n); ++i) {
            for (int j = 1; j <= maxValue; ++j) {
                for (int k = j * 2; k <= maxValue; k += j) {
                    dp[k][i + 1] = (dp[k][i + 1] + dp[j][i]) % mod;
                }
            }
        }
        for (int i = 1; i <= min(14, n); ++i)
            for (int j = 1; j <= maxValue; ++j) a[i] = (a[i] + dp[j][i]) % mod;
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = i * fac[i - 1] % mod;
        ifac[n] = inv(fac[n]);
        for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
        ll ans = 0;
        for (int i = 1; i <= min(n, 14); ++i) { 
            ll tmp = binomial(n - 1, i - 1);
            ans = (ans + a[i] * tmp % mod) % mod;
        }
        return ans;
    }
};