#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& v : a) cin >> v;
	int l = 1, r = n - 2;
	while (l < n && a[l] == a[0]) ++l;
	while (r >= 0 && a[r] == a[n - 1]) --r;
	if (l == n) {
		cout << 0 << '\n';
		return;
	}
	// [0, l), (r, n-1]
	if (a[0] == a[n - 1]) {
		cout << n - l - (n - 1 - r) << '\n';
	}
	else {
		cout << n - max(l, n - 1 - r) << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) solve();
}