#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
	int n;
	ll m;
	cin >> n >> m;
	vector<int> a(n);
	for (int& v : a) cin >> v;
	sort(a.begin(), a.end());
	if (n == 1) {
		cout << 0 << endl;
		return;
	}
	int p = lower_bound(a.begin(), a.end(), m) - a.begin();
	ll x = inf, y = inf; 
	if (p <= 0) x = min(x, a[n - 2] - m);
	if (p <= 1) y = min(y, a[n - 1] - m);
	if (p >= n - 1) x = min(x, m - a[0]);
	if (p >= n) y = min(y, m - a[1]);
	x = min(x, min(abs(m - a[n - 2]), abs(m - a[0])) + abs(a[0] - a[n - 2]));
	y = min(y, min(abs(m - a[1]), abs(m - a[n - 1])) + abs(a[1] - a[n - 1]));
	cout << min(x, y) << endl;
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	solve();
}