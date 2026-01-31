#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int maxn = 1010;
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

void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

int flag = 0;

class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        if (!flag) {
            flag = 1;
            init(1000);
        }
        // -1, 1, s = endPos - startPos
        int s = abs(endPos - startPos);
        // x + y = k, x - y = s
        // 2x = k + s
        if ((k+s)%2) return 0;
        int x = (k+s)/2;
        if (k < x) return 0;
        // C(k,x), k!/x!(k-x)!
        return binomial(k,x);
    }
};