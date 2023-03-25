#include <bits/stdc++.h>
using namespace std;

// If there is at least one element of type 0 and at least one element of type 1
// , we can always sort the array.

// 特殊到一般的推导技巧

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);

	for (int i = 0; i < n; ++i)
		cin >> a[i];
	int t;
	bool h_0 = false, h_1 = false;
	for (int i = 0; i < n; ++i) {
		cin >> t;
		if (!t) h_0 = true;
		else h_1 = true;
	}
	cout << (is_sorted(a.begin(), a.end()) || (h_0 && h_1) ? "Yes" : "No") << endl;
}


int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) solve();
}