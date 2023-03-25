#include <bits/stdc++.h>
using namespace std;


void solve() {
	int m;
	int t;
	cin >> m;

	vector<vector<int>> sum(2, vector<int>(m + 1, 0));

	for (int row = 0; row <= 1; ++row)
		for (int i = 1; i <= m; ++i) {
			cin >> sum[row][i];
			sum[row][i] += sum[row][i - 1];
		}
	// the down position
	int ans = 2e9;
	for (int i = 1; i <= m; i++) {
		int a = sum[0][i];
		int c = max(sum[0][m] - a, sum[1][i - 1]);
		ans = min(ans, c);
	}
	cout << ans << endl;
}


int main() {
	ios::sync_with_stdio(false);
	int T = 1;
	cin >> T;
	while (T--)
		solve();
}