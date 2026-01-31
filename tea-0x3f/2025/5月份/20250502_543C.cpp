// https://codeforces.com/problemset/problem/543/C
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	vector a(n, vector<char>(m));
	vector b(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> b[i][j];
		}
	}
	vector<int> dp((1 << n), inf);
	vector<int> cost((1 << n), inf);
	for (int j = 0; j < m; ++j) {
		vector<int> s(26);
		vector<int> sc(26);
		for (int i = 0; i < n; ++i) {
			int c = a[i][j] - 'a';
			s[c] |= (1 << i);
			sc[c] += b[i][j];
			cost[1 << i] = min(cost[1 << i], b[i][j]);
		}
		for (int i = 0; i < 26; ++i) {
			if (s[i] == 0) continue;
			for (int k = 0; k < n; ++k) {
				if ((s[i] >> k) & 1) {
					cost[s[i]] = min(cost[s[i]], sc[i] - b[k][j]);
				}
			}
		}
	}
	dp[0] = 0;
	for (int x = 1; x < (1 << n); ++x) {
		if (cost[x] < inf) {
			for (int i = 0; i < (1 << n); ++i) {
				dp[i | x] = min(dp[i | x], dp[i] + cost[x]);
			}
		}
	}
	std::cout << dp[(1 << n) - 1] << endl;
}