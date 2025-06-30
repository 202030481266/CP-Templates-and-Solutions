#include <bits/stdc++.h>
// #include "stdafx.h"
using namespace std;
using ll = long long;
using ull = unsigned long long;

void solve() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int& v : arr) cin >> v;
	vector<int> cnt(30);
	for (int v : arr) {
		for (int i = 0; i < 30; ++i) {
			if ((v >> i) & 1) ++cnt[i];
		}
	}
	ull ans = 0;
	for (int v : arr) {
		ull res = 0;
		for (int i = 0; i < 30; ++i) {
			if ((v >> i) & 1) {
				res += (ull)(n - cnt[i]) * (1 << i);
			}
			else {
				res += (ull)cnt[i] * (1 << i);
			}
		}
		ans = max(ans, res);
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