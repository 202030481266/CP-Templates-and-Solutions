class Solution {
public:
	int minTrioDegree(int n, vector<vector<int>>& edges) {
		vector<int> cnt(n + 1);
		vector<vector<bool>> a(n + 1, vector<bool>(n + 1, false));

		for (auto c : edges) {
			++cnt[c[0]]; 
			++cnt[c[1]];
			a[c[0]][c[1]] = true;
			a[c[1]][c[0]] = true;
		}

		int ans = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				for (int k = j + 1; k <= n; ++k) {
					if (a[i][j] && a[i][k] && a[k][j]) {
						ans = min(ans, cnt[i] + cnt[j] + cnt[k] - 6);
					}
				}
			}
		}
		return ans == INT_MAX ? -1 : ans;
	}
};