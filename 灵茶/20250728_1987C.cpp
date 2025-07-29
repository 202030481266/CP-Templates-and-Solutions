#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& v : a) cin >> v;
	int cur = a[n - 1];
	for (int i = n - 2; i >= 0; --i) {
		cur = max(cur + 1, a[i]);
	}
	cout << cur << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}