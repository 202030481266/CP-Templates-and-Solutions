// 非常好的一道二项式反演的题目，使用容斥原理进行建模
// 计算简单的总的一种方案数，反演得到很难计算的特定方案数
// 建模： 钦定k个且至少 转换为 恰好k个，本质上是容斥原理

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int mod = 1e9 + 7;
const int maxn = 1000010;
long long fac[maxn], ifac[maxn];

int n, k;

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


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    init();
    vector<ll> g(n+1);
    g[n] = 2;
    for (int i = n-1; i >= 0; --i) g[i] = g[i+1] * g[i+1] % mod;
    for (int i = 0; i <= n; ++i) {
        g[i] = (g[i] + mod - 1) % mod * binomial(n, i) % mod;
    }

    // 二项式反演
    ll ans = 0;
    // f[k] = sum(i=k, n) * (-1) ^ (i-k) * binom{i}{k} * g[i]
    for (int i = k; i <= n; ++i) {
        if ((i-k) & 1) {
            ans = (ans - binomial(i, k) * g[i] % mod + mod) % mod;
        }
        else {
            ans = (ans + binomial(i, k) * g[i] % mod) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}