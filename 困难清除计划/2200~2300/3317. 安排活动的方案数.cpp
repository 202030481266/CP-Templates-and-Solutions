#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1003;
ll S[maxn][maxn];

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

    // 初始化逆元
    int N = 1000;
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = inv(fac[N]);
	for (int i = N-1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    // 初始化第二类斯特林数字
    S[0][0] = 1;
    S[N][0] = 0;
    for(int i = 1; i <= N; ++ i) {
        for(int j = 1; j <= i; ++ j) {
            S[i][j] = (S[i- 1][j - 1] + 1ll * j * S[i - 1][j]) % mod;
        }
    }
}

class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        init();
        int m = min(n, x);
        vector<ll> py(m+1); 
        py[0] = 1;
        for (int i = 1; i <= m; ++i) py[i] = py[i-1] * y % mod;
        ll ans = 0;
        for (int i = 1; i <= m; ++i) {
            ans = (ans + (py[i] * fac[i] % mod * binomial(x, i) % mod * S[n][i] % mod)) % mod;
        }
        return ans;
    }
};