// https://codeforces.com/problemset/problem/2101/C
// 非常巧妙的贪心，前后缀分解之后一个一个计算贡献而不是计算 j-i
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int maxn = 200005;

int n, a[maxn], f[maxn][2];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	set<int> s;
	for (int i = 1; i <= n; ++i) s.insert(i);
	for (int i = 0; i < n; ++i) {
		auto it = s.upper_bound(a[i]);
		if (it != s.begin()) s.erase(prev(it));
		f[i][0] = n - s.size();
	}
	s.clear();
	for (int i = 1; i <= n; ++i) s.insert(i);
	for (int i = n - 1; i >= 0; --i) {
		auto it = s.upper_bound(a[i]);
		if (it != s.begin()) s.erase(prev(it));
		f[i][1] = n - s.size();
	}
	ll ans = 0;
	for (int i = 0; i < n - 1; ++i) ans += min(f[i][0], f[i + 1][1]);
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}