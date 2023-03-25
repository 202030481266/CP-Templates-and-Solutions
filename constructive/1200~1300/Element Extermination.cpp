#include <bits/stdc++.h>
using namespace std;



void solve() {
	int n;
	int p_1;
	cin >> n;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] == 1) p_1 = i;
	}
	if (p_1 == n) {
		cout << "NO" << endl;
		return;
	}
	else if (p_1 == 1)  {
		cout << "YES" << endl;
		return;
	} 
	else {
		cout << (a[1] < a[n] ? "YES" : "NO") << endl;
	}
}


int main() {
	ios::sync_with_stdio(false);
	int T = 1;
	cin >> T;
	while (T--) solve();
}