#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


ll quick_pow(ll a, ll b) {
	ll res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	if (k > n || k == 1) {
		cout << quick_pow(m, n) << '\n';
	}
	else if (k == n) {
		cout << quick_pow(m, (n + 1) / 2) << '\n';
	}
	else {
		if (k % 2 == 0) {
			cout << m << endl;
		}
		else {
			ll ans = 1ll * m * m;
			cout << (ans % mod) << endl;
		}
	}
}