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

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	vector<int> arr(n);
	vector<tuple<int, int, int>> queries;
	vector<int> base(20);
	vector<int> pw(n + 1);
	for (int i = 0; i < n; ++i) cin >> arr[i];
	for (int i = 0, l, x; i < m; ++i) {
		cin >> l >> x;
		queries.emplace_back(l, x, i);
	}
	sort(queries.begin(), queries.end());
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 2 % mod;
	int p = 0, tot = 0;
	vector<int> ans(m);
	for (int i = 0; i < n; ++i) {
		int flag = 0;
		for (int j = 19; j >= 0; --j) {
			if ((arr[i] >> j) & 1) {
				if (base[j]) arr[i] ^= base[j];
				else {
					base[j] = arr[i];
					flag = 1;
					break;
				}
			}
		}
		if (!flag) ++tot;
		while (p < m && get<0>(queries[p]) == i + 1) {
			int x = get<1>(queries[p]), id = get<2>(queries[p]);
			flag = 1;
			for (int j = 19; j >= 0; --j) {
				if ((x >> j) & 1) {
					if (base[j]) x ^= base[j];
					else {
						flag = 0;
						break;
					}
				}
			}
			if (flag) {
				ans[id] = pw[tot];
			}
			++p;
		}
	}
	for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}