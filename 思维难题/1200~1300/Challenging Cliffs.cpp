#include <bits/stdc++.h>
using namespace std;



const int N = 200010;
int a[N];
void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	if (n == 2) {
		for (int i = 0; i < n; ++i) 
			cout << a[i] << (i == n - 1 ? '\n' :  ' ');
		return;
	} 
	int rs = INT_MAX, pos;
	for (int i = 1; i < n; ++i)
		if (a[i] - a[i - 1] < rs) rs = a[i] - a[i - 1], pos = i;
	// 输出
	for (int i = pos; i < n; ++i) cout << a[i] << ' ';
	for (int i = 0; i < pos; ++i) cout << a[i] << (i == pos - 1 ? '\n' : ' ');
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}
