class Solution {
    static constexpr int mod = 1e9 + 7;
    vector<long long> fac, ifac;
public:
    long long quick_power(long long a, long long b, int p = mod) { 
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
    int numberOfSequence(int n, vector<int>& sick) {
        // 组合数学简单题目

        int m = sick.size();

        fac.resize(n + 10);
        ifac.resize(n + 10);

        // 初始化逆元
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = inv(fac[n]);
        for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;

        // 寻找所有的k
        long long ans = 1, N = n - m, tot = 0, cnt = 0;

        for (int i = 0; i + 1 < m; ++i) {
            long long k = sick[i + 1] - sick[i] - 1; 
            if (k == 0) continue;
            ans = ans * binomial(N, k) % mod;
            N -= k;
            tot += k;
            ++cnt;
        }

        // [0, sick[0])
        long long pre = sick[0];
        ans = ans * quick_power(2, tot - cnt) % mod * binomial(N, pre) % mod;
        return ans;
    }
};