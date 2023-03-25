#include <bits/stdc++.h>
using namespace std;

// 周期性构造


void solve() {
	// it means the s[i]... s[i + k - 1], s[i + k]...
	// s[i] == s[i + k], so it is period
	int n, k;
	cin >> n >> k;
	set<int> s;
	for (int i = 1; i <= n; i++) {
		int t;
		cin >> t;
		s.emplace(t);
	}
	// no more k distinic numbers
	if (s.size() > k) {
		cout << -1 << endl;
		return;
	}
	cout << n * k << endl;
	for (int i = 1; i <= n; ++i) {
		for (auto c : s) cout << c << ' ';
		for (int j = 1; j <= k - s.size(); ++j) 
			cout << 1 << ' ';
	}
	cout << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) solve();
}