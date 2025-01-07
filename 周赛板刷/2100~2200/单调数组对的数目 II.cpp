#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution_dp {
public:
    int countOfPairs(vector<int>& nums) {
        int n  = nums.size();
        // dp的做法非常简单
        // dp[i][x] = sum (dp[i-1][min(x,nums[i-1]-nums[i]+x)])
        // 做一个前缀和优化就可以过掉
        int start = 0, V = nums[0]+1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i-1]) 
                start += nums[i] - nums[i-1];
            if (start > nums[i]) return 0;
            V = min(V, nums[i]-start+1);
        }
        vector<int> dp(V,1);
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < V; --j) {
                dp[j] = (dp[j] + dp[j-1]) % mod;
            }
        }
        int ans = 0;
        for (int i = 0; i < V; ++i) ans = (ans + dp[i]) % mod;
        return ans;
    }
};

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
const int N = 3000;
long long fac[3002], ifac[3002];
long long binomial(int x, int y) {
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
bool flag = false;
void init() {
    if (flag) return;
    flag = true;
    fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = inv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        init();
        int n  = nums.size(),start = 0, V = nums[0]+1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i-1]) 
                start += nums[i] - nums[i-1];
            if (start > nums[i]) return 0;
            V = min(V, nums[i]-start+1);
        }
        return binomial(n+V-1,n);
    }
};