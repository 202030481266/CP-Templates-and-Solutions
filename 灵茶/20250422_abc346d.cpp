// https://atcoder.jp/contests/abc346/tasks/abc346_d
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<char> s(n);
	vector<ll> cost(n);
	for (char& c : s) cin >> c;
	for (ll& c : cost) cin >> c;
	vector<ll> a0(n), a1(n), b0(n), b1(n);
	if (s[0] == '0') a0[0] = 0, a1[0] = cost[0];
	else a0[0] = cost[0], a1[0] = 0;
	if (s[n - 1] == '0') b0[n - 1] = 0, b1[n - 1] = cost[n - 1];
	else b0[n - 1] = cost[n - 1], b1[n - 1] = 0;
	for (int i = 1; i < n; ++i) {
		a0[i] = a1[i - 1] + (s[i] == '0' ? 0 : cost[i]);
		a1[i] = a0[i - 1] + (s[i] == '1' ? 0 : cost[i]);
	}
	for (int i = n - 2; i >= 0; --i) {
		b0[i] = b1[i + 1] + (s[i] == '0' ? 0 : cost[i]);
		b1[i] = b0[i + 1] + (s[i] == '1' ? 0 : cost[i]);
	}
	ll ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 0; i + 1 < n; ++i) {
		ans = min(ans, min(a0[i] + b0[i + 1], a1[i] + b1[i + 1]));
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}