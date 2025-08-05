#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


void solve() {
	int n, k;
	cin >> n >> k;
	vector<array<int, 3>> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i][1] >> arr[i][2] >> arr[i][0];
	}
	sort(arr.begin(), arr.end());
	for (auto [val, l, r] : arr) {
		if (l <= k && k <= r && val > k) k = val;
	}
	cout << k << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}