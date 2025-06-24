// https://codeforces.com/problemset/problem/2107/C
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
	int n;
	ll k;
	cin >> n >> k;
	vector<char> s(n);
	vector<ll> a(n);
	for (char& c : s) cin >> c;
	for (ll& v : a) cin >> v;
	vector<ll> limit(n, k);
	for (int i = n - 1; i >= 1; --i) {
		if (s[i] == '0') continue;
		if (a[i] == 0) {
			limit[i - 1] = min(limit[i - 1], limit[i]);
		}
		else if (a[i] > 0) {
			limit[i - 1] = min(limit[i - 1], limit[i] - a[i]);
		}
		else {
			limit[i - 1] = min(limit[i - 1], limit[i] - a[i]);
		}
	}
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1' && a[i] > limit[i]) {
			cout << "No" << '\n';
			return;
		}
	}
	int flag = 0;
	vector<ll> dp(n);
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1') {
			dp[i] = a[i];
			if (i > 0 && dp[i - 1] > 0) dp[i] += dp[i - 1];
		}
		else {
			dp[i] = limit[i];
			if (i > 0 && dp[i - 1] > 0) a[i] = dp[i] - dp[i - 1];
			else a[i] = dp[i];
		}
		// assert(dp[i] <= k);
		if (dp[i] == k) flag = 1;
	}
	if (flag) {
		cout << "Yes" << '\n';
		for (int i = 0; i < n; ++i) cout << a[i] << ' ';
		cout << '\n';
	}
	else {
		cout << "No" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}