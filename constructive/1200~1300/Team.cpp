#include <bits/stdc++.h>
using namespace std;



void solve() {
	int n, m;
	cin >> n >> m;

	if (n - 1 > m) {
		cout << -1 << endl;
		return;
	}
	int t = ((m & 1) ? m + 1 : m);
	if (t / 2 - 1 > n) {
		cout << -1 << endl;
		return;
	}
	if (m >= n) {
		int g = (m - n);
		if (g > n) {
			if (g - n == 1) cout << "1";
			if (g - n == 2) cout << "11";
			g = n;
		}
		for (int i = 0; i < g; ++i)
			cout << "011";
		for (int i = 0; i < (n - g); ++i)
			cout << "01";
		cout << endl;
	} else {
		for (int i = 0; i < n - 1; ++i)
			cout << "01";
		cout << "0" << endl;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int T = 1;
	while (T--) solve();
}