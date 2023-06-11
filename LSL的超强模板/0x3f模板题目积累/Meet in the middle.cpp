/*
	O(n*2^(n/2))
	author: xiaoshulin
	Question: https://www.luogu.com.cn/problem/P2962
*/


typedef long long ll;
int n, m, ans = 0x7f7f7f7f;
map<ll, int> f;
ll a[40];

int main() {
	cin >> n >> m;
	a[0] = 1;
	for (int i = 1; i < n; ++i) a[i] = a[i - 1] * 2;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u, --v;
		a[u] |= (1ll << v);
		a[v] |= (1ll << u);
	}
	for (int i = 0; i < (1 << (n / 2)); ++i) {
		ll t = 0;
		int cnt = 0;
		for (int j = 0; j < n / 2; ++j) {
			if ((i >> j) & 1) {
				t ^= a[j];
				++cnt;
			}
		}
		if (!f.count(t)) f[t] = cnt;
		else f[t] = min(f[t], cnt);
	}
	for (int i = 0; i < (1 << (n - n / 2)); ++i) {
		ll t = 0;
		int cnt = 0;
		for (int j = 0; j < (n - n / 2); ++j) {
			if ((i >> j) & 1) {
				t ^= a[n / 2 + j];
				++cnt;
			}
		}
		if (f.count(((1ll << n) - 1) ^ t))
			ans = min(ans, cnt + f[((1ll << n) - 1) ^ t]);
	}
	cout << ans;
}

