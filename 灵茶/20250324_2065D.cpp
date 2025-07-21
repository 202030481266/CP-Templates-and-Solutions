#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 305;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<ll>> arr;
	for (int i = 0; i < n; ++i) {
		vector<ll> tmp(m);
		for (ll& v : tmp) cin >> v;
		arr.push_back(tmp);
	}
	vector<int> ids(n);
	vector<ll> sum(n);
	for (int i = 0; i < n; ++i) {
		for (ll v : arr[i]) sum[i] += v;
	}
	iota(ids.begin(), ids.end(), 0);
	sort(ids.begin(), ids.end(), [&](int i, int j) {
		return sum[i] > sum[j];
		});
	ll ans = 0, cur = 0;
	for (int idx : ids) {
		for (int i = 0; i < m; ++i) {
			cur += arr[idx][i];
			ans += cur;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) solve();
}
