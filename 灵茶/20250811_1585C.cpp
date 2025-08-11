#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;



void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> a;
	vector<int> b;
	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		if (x < 0) b.push_back(-x);
		if (x > 0) a.push_back(x);
	}
	ranges::sort(a);
	ranges::sort(b);
	ll ans = 0;
	for (int i = a.size() - 1; i >= 0; i -= k) ans += 2 * a[i];
	for (int i = b.size() - 1; i >= 0; i -= k) ans += 2 * b[i];
	int lasta = (a.size() ? a.back() : 0), lastb = (b.size() ? b.back() : 0);
	cout << ans - max(lasta, lastb) << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}