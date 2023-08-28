#include <bits/stdc++.h>

using namespace std;



// 考虑奇偶分组


void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	long long sum = 0;

	for (int &c : a) cin >> c, sum += c;

	long long c = 0;
	for (int i = 0; i < n; ++i) {
		if (i & 1) c += (a[i] - 1);
	}

	if (c * 2 <= sum) {
		for (int i = 0; i < n; ++i) {
			if (i & 1) cout << 1 << ' ';
			else cout << a[i] << ' ';
		}
	}
	else {
		for (int i = 0; i < n; ++i) {
			if (i & 1) cout << a[i] << ' ';
			else cout << 1 << ' ';
		}
	}
	return;
}




int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}


	return 0;
}