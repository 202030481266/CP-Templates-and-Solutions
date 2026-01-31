//  https://atcoder.jp/contests/abc367/tasks/abc367_d
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 2e5 + 7;

int n, m;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	vector<int> cnt(m);
	vector<int> a(n * 2 + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[n + i] = a[i];
	}
	for (int i = 1; i <= 2 * n; ++i) {
		a[i] = (a[i] + a[i - 1]) % m;
	}
	int l = 0;
	long long ans = 0;
	cnt[0] = 1;
	for (int i = 1; i < 2 * n; ++i) {
		while (i - l > n - 1) {
			--cnt[a[l++]];
		}
		if (i >= n) ans += cnt[a[i]];
		++cnt[a[i]];
	}
	cout << ans << '\n';
}