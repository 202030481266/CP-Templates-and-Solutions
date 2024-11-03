#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 100;
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

bool flag = false;

void init() {
    if (flag) return;
    flag = true;
	fac[0] = 1;
    int n = 80;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

ll dp[800][100];

class Solution {
public:
    int countBalancedPermutations(string num) {
        init();
        int n = num.size(), odd = (n+1) / 2, even = n / 2;
        int bits = 0, sum = 0;
        vector<int> cnt(10);
        for (char c : num) ++cnt[c - '0'], sum += (c-'0');
        if (sum & 1) return 0;
        sum /= 2;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < 10; ++i) {
            if (cnt[i]) {
                bits += cnt[i];
                for (int s = sum; s >= 0; --s) {
                    for (int x = min(bits, odd); x >= 0; --x) {
                        int y = bits - x; // even
                        if (y > even) continue;
                        // x odd, y even
                        int tmp = 0;
                        for (int k = 0; k <= min(x, cnt[i]) && k * i <= s; ++k) {
                            if (cnt[i] - k > y) continue;
                            tmp = (tmp + dp[s-k*i][x-k] * binomial(x, k) % mod * binomial(y, cnt[i]-k) % mod) % mod;
                        }
                        dp[s][x] = tmp;
                    }
                }
            }
        }
        return dp[sum][odd];
    }
};