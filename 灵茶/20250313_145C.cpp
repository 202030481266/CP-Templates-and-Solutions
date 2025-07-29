#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n, m;

long long fac[maxn], ifac[maxn];

long long quick_power(long long a, long long b, int p) {
	long long ans = 1 % p;
	for (; b; b >>= 1) {
		if (b & 1) ans = ans * a % p;
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


bool check(int val) {
	while (val) {
		if (val % 10 != 4 && val % 10 != 7) return false;
		val /= 10;
	}
	return true;
}

ll dp[2000];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	vector<int> arr(n);
	for (int& v : arr) cin >> v;
	unordered_map<int, int> cnt;
	for (int v : arr) {
		if (check(v)) {
			++cnt[v];
		}
	}
	ll ans = 0;
	dp[0] = 1;
	int N = cnt.size(), tot = 0;
	for (auto [_, v] : cnt) {
		tot += v;;
		for (int i = N; i >= 1; --i) {
			dp[i] = (dp[i] + dp[i - 1] * v % mod) % mod;
		}
	}
	init();
	for (int i = 0; i <= min(N, m); ++i) {
		if (m - i <= n - tot) ans = (ans + dp[i] * binomial(n - tot, m - i) % mod) % mod;
	}
	cout << ans << '\n';
}