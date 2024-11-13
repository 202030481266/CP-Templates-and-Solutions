#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
const int maxn = 1010;
long long fac[maxn], ifac[maxn];

int a, b, N, n, m;

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

void init() {
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = inv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

int main() {
    cin >> a >> b >> N >> n >> m;
    init();
    // 
    cout << (binomial(N, m) * quick_power(a, n) % mod * quick_power(b, m) % mod) << endl;
}
