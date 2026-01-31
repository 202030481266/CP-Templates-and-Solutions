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
    if (y > x) return 0;
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
void init() {
	fac[0] = 1;
    int n = 100000;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
bool flag = false;

class Solution {
public:
    int minMaxSums(vector<int>& nums, int K) {
        if (!flag) {
            flag = true;
            init();
        }
        int n = nums.size();
        vector<int> a = nums;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        n = a.size();
        vector<int> cnt(n);
        for (int& v : nums) {
            v = lower_bound(a.begin(), a.end(), v) - a.begin();
            cnt[v]++;
        }
        vector<ll> sum(n+1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + cnt[i];
        }
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= K; ++k) {
                int mn = sum[i-1], mx = sum[n] - sum[i];
                ans = (ans + binomial(mn + cnt[i-1], k) * a[i-1] % mod) % mod;
                if (mn >= k) ans = (ans - binomial(mn, k) * a[i-1] % mod + mod) % mod;
                ans = (ans + binomial(mx + cnt[i-1], k) * a[i-1] % mod) % mod;
                if (mx >= k) ans = (ans - binomial(mx, k) * a[i-1] % mod + mod) % mod;
            }
        }
        return ans;
    }
};