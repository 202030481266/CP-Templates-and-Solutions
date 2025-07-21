#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(m);
	for (int& v : a) cin >> v;
	for (int& v : b) cin >> v;
	sort(b.begin(), b.end());
	a[0] = min(a[0], b[0] - a[0]);
	for (int i = 1; i < n; ++i) {
		int x = a[i - 1] + a[i];
		auto it = lower_bound(b.begin(), b.end(), x);
		if (it == b.end()) {
			if (a[i] < a[i - 1]) {
				cout << "NO" << '\n';
				return;
			}
		}
		else {
			if (a[i] >= a[i - 1]) a[i] = min(a[i], *it - a[i]);
			else a[i] = *it - a[i];
		}
	}
	cout << "YES" << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) solve();
}
