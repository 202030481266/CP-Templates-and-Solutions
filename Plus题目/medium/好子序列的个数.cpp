#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 10010;
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

bool init = false;
void f(int n) {
    if (init) return;
    init = true;
    fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

class Solution {
public:
    int countGoodSubsequences(string s) {
        f(10000);
        int n = s.size();
        vector<int> cnt(26);
        for (char c : s)  ++cnt[c-'a'];
        ll ans = 0;
        vector<int> tmp;
        int mn = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i]) {
                tmp.push_back(cnt[i]);
                mn = max(mn, cnt[i]);
            }
        }
        for (int i = 1; i <= mn; ++i) {
            ll res = 1;
            for (int v : tmp) res *= (1+binomial(v, i)), res %= mod;
            ans = (ans+res-1+mod) % mod;
        }
        return ans;
    }
};