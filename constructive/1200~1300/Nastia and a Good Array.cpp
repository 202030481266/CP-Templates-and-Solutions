#include <bits/stdc++.h>
using namespace std;



void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	bool flag = true;
	for (int i = 2; i <= n; ++i)
		if (__gcd(a[i], a[i - 1]) != 1) flag = false;
	if (flag) {
		cout << 0 << endl;
		return;
	}

	int mn = 1;
	for (int i = 2; i <= n; ++i)
		if (a[i] < a[mn]) mn = i;

	cout << n - 1 << endl;
	for (int i = 1; i <= n; ++i) {
		// always change 
		if (i == mn) continue;
		cout << mn << ' ' << i << ' ' << a[mn] << ' ' << a[mn] + abs(i - mn) << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
		solve();
}