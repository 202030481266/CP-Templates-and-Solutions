#include <bits/stdc++.h>
using namespace std;

// swap(ai, aj) if gcd(ai, aj) is small
// 还是经典的中介构造法，推导出一般的结论

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) 
		cin >> a[i];

	if (is_sorted(a.begin(), a.end())) {
		cout << "YES" << endl;
		return;
	}

	vector<int> b(a.begin(), a.end());
	sort(a.begin(), a.end());
	int mn = a[0];
	// get the number need to be swap
	bool flag = true;
	for (int i = 0; i < n; ++i) 
		if (a[i] != b[i] && a[i] % mn > 0) 
			flag = false;

	cout << (flag ? "YES" : "NO") << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) solve();
}