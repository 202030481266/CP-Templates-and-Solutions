// https://codeforces.com/problemset/problem/2086/D
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

static constexpr int mod = 998'244'353;
static constexpr int maxn = 500007;
int cnt[26];
ll dp[maxn];

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

void init(int n=500000) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

void cf2086D() {
    int sum = 0, odd = 0, mid;
    for (int i = 0; i < 26; ++i) {
        cin >> cnt[i];
        sum += cnt[i];
        if (cnt[i] & 1) ++odd;
    }
    mid = (sum + 1) / 2;
    for (int i = 0; i < 26; ++i) {
	    if (cnt[i] > mid) {
            cout << 0 << '\n';
            return;
	    }
    }
    if ((sum & 1) ^ (odd & 1)) {
        cout << 0 << '\n';
        return;
    }
    memset(dp, 0, sizeof(dp));
    int cur = 0;
    dp[0] = 1;
    for (int i = 0; i < 26; ++i) {
	    if (cnt[i]) {
            cur += cnt[i];
            // dp[i][x] = dp[i-1][x-cnt[i]] * binomial(x, cnt[i]) + dp[i-1][x] * binomial(cur-x, cnt[i])
            for (int x = min(cur, mid); x >= 0; --x) {
                if (cur-x >= cnt[i]) dp[x] = dp[x] * binomial(cur-x, cnt[i]) % mod;
                if (x >= cnt[i]) dp[x] = (dp[x] + dp[x-cnt[i]] * binomial(x, cnt[i]) % mod) % mod;
            }
	    }
    }
    cout << dp[mid] << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    init();
    while (t--) cf2086D();
}
