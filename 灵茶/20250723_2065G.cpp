#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 200005;

int n;
int arr[maxn], divisors[maxn], lp[maxn];
vector<int> primes;

ll cnt[maxn];

void init(int n = 200000) {
	lp[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			primes.push_back(i);
		}
		for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j) lp[i * primes[j]] = primes[j];
	}
	for (int i = 1, x; i <= n; ++i) {
		x = i;
		while (x != 1) {
			++divisors[i];
			x /= lp[x];
		}
	}
}

int vis[maxn];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	// lcm (a, b) is a half-prime , means that a is prime or b is prime || a is a half prime and b is the a % b == 0 || b % a == 0 and b is half-prime
	vector<int> d_ps, d_halfs;
	for (int i = 1; i <= n; ++i) {
		if (lp[arr[i]] == arr[i]) {
			++cnt[arr[i]];
			if (!vis[arr[i]]) {
				vis[arr[i]] = 1;
				d_ps.push_back(arr[i]);
			}
		}
		if (divisors[arr[i]] == 2) {
			++cnt[arr[i]];
			if (!vis[arr[i]]) {
				vis[arr[i]] = 1;
				d_halfs.push_back(arr[i]);
			}
		}
	}
	ll ans = 0, sum = 0;
	for (int v : d_ps) {
		ans += sum * cnt[v]; // only with pre elements
		sum += cnt[v];
	}
	for (int v : d_halfs) {
		ans += cnt[v] + cnt[v] * (cnt[v] - 1) / 2; // one or two
	}
	for (int v : d_halfs) {
		if (lp[v] == v / lp[v]) ans += cnt[v] * cnt[lp[v]];
		else ans += cnt[v] * (cnt[lp[v]] + cnt[v / lp[v]]);
	}
	cout << ans << '\n';
	for (int v : d_ps) cnt[v] = vis[v] = 0;
	for (int v : d_halfs) cnt[v] = vis[v] = 0;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	init();
	while (t--) solve();
}
