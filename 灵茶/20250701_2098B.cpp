#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 200005;

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> arr(n);
	for (int& v : arr) cin >> v;
	sort(arr.begin(), arr.end());
	vector<array<int, 2>> b;
	int p = 0;
	while (p < n) {
		int i = p + 1;
		while (i < n && arr[i] == arr[p]) ++i;
		b.push_back({ arr[p], i - p });
		p = i;
	}
	int ans = 0, m = b.size(), cur = 0, l = 0;
	for (int i = 0; i < m; ++i) {
		int delta = abs(n - 2 * cur);
		if (delta <= k) { // (l, b[i][0])
			ans += b[i][0] - l - 1;
		}
		// b[i][0]
		delta = abs((n - b[i][1]) - 2 * cur);
		if (delta <= k + b[i][1]) {
			++ans;
		}
		l = b[i][0];
		cur += b[i][1];
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}