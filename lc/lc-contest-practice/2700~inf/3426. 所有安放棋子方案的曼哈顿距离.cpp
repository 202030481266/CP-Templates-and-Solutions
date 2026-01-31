#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 非常困难的问题
// 解决方式是贡献法，只关注其中的一对点的贡献
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
    int n = 100000;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

int flag = 0;

class Solution {
public:
    int distanceSum(int m, int n, int k) {
        if (!flag) {
            flag = 1;
            init();
        }
        ll x = 1ll * n * (n - 1) * (n + 1) / 6;
        ll y = 1ll * m * (m - 1) * (m + 1) / 6;
        ll ans = (x * m * m + y * n * n) % mod;
        return ans * binomial(m * n - 2, k - 2) % mod;
    }
};