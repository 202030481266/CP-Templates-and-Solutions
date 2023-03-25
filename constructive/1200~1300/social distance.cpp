#include <bits/stdc++.h>
using namespace std;

// 贪心： 一直往前匹配就可以了

void solve() {
	int n, k;
	string pos;
	cin >> n >> k;
	cin >> pos;

	vector<int> sum(n + 1);
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + (pos[i - 1] == '1');

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int upper = min(n, i + k);
		int lower = max(1, i - k);
		if (sum[upper] - sum[lower - 1] == 0) {
			i = i + k;
			++ans;
		}
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--) solve();
}