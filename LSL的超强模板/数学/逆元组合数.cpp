#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
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
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
