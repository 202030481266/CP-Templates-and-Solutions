#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 截止2025/5/4,今年做过最难的题目了,想了很多岔路和优化方法
// 还好dp基础不弱，最后还是暴力过掉了(正解就是暴力，玄学复杂度导致我想了很久很久!)

const int maxn = 60;
long long fac[maxn], ifac[maxn];

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

ll dp[51][31][31][31];
int ones[55];
bool inited = false;

void init() {
    for (int i = 0; i < 55; ++i) ones[i] = __builtin_popcount(i);
	fac[0] = 1;
    int n = 55;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

class Solution {
public:
    int magicalSum(int M, int K, vector<int>& nums) {
        if (!inited) {
            inited = true;
            init();
        }
        int n = nums.size();
        for (int i = 1; i <= n; ++i) { // 初始化
            for (int m = 0; m <= M; ++m) {
                for (int j = 0; j <= M; ++j) {
                    for (int k = 0; k <= M; ++k) {
                        dp[i][m][j][k] = 0;
                    }
                }
            }
        }
        dp[0][0][0][0] = 1;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][0][0][0] = 1;
            for (int m = 1; m <= M; ++m) {
                for (int j = 0; j <= m; ++j) { // 2^{i-1}结尾, 有j个
                    for (int k = 1; k <= m; ++k) {
                        if (j == 0) {
                            for (int pre = 0; pre <= m; ++pre)
                                dp[i][m][pre / 2][k] = (dp[i][m][pre / 2][k] + dp[i-1][m][pre][k]) % mod;
                        }
                        else {
                            for (int pre = 0; pre <= m - j; ++pre) {
                                // pre_k - count(pre / 2) + count(pre / 2 + j) = k
                                int pre_k = k - ones[pre / 2 + j] + ones[pre / 2];
                                if (pre_k < 0 || pre_k > M) continue;
                                int tmp = dp[i-1][m-j][pre][pre_k] * quick_power(nums[i-1], j) % mod * binomial(M - m + j, j) % mod;
                                // m - j is used, M - m + j is not used
                                if (m == M && k == K) ans = (ans + tmp) % mod;
                                dp[i][m][j + pre / 2][k] = (dp[i][m][j + pre / 2][k] + tmp) % mod;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};