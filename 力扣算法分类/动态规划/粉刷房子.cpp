// https://leetcode.cn/problems/paint-house-iii/



class Solution {
public:
	int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
		swap(n, m);
		vector c(n + 1, vector(n + 1, vector<int>(m + 1, 0)));
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				for (int k = 1; k <= m; ++k) {
					// i ~ j all is the color k to cost
					bool flag = true;
					int sum = 0;
					for (int house = i; house <= j; ++house) {
						if (houses[house - 1] > 0 && houses[house - 1] != k) flag = false;
						if (!houses[house - 1])
							sum += cost[house - 1][k - 1];
					}
					if (flag) c[i][j][k] = sum;
					else c[i][j][k] = 0x3f3f3f3f;
				}
			}
		}
		vector dp(n + 1, vector(target + 1, vector<int>(m + 1, 0x3f3f3f3f)));
		vector f(n + 1, vector(target + 1, vector<int>(m + 1, 0x3f3f3f3f)));
		fill(dp[0][0].begin(), dp[0][0].end(), 0);
		fill(f[0][0].begin(), f[0][0].end(), 0);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= min(i, target); ++j) {
				for (int k = 1; k <= m; ++k) {
					for (int x = 1; x <= i; ++x) {
						// means [x, i] is all the color of k
					/*	for (int y = 1; y <= m; ++y) {
							if (y != k)
								dp[i][j][k] = min(dp[i][j][k], dp[x - 1][j - 1][y] + c[x][i][k]);
						}*/
						dp[i][j][k] = min(dp[i][j][k], f[x - 1][j - 1][k] + c[x][i][k]);
					}
				}
				// get the minimum number of the dp[i][j]
				vector<int> pre(m + 2, 0x3f3f3f3f), suf(m + 2, 0x3f3f3f3f);
				for (int k = 1; k <= m; ++k) pre[k] = min(pre[k - 1], dp[i][j][k]);
				for (int k = m; k >= 1; --k) suf[k] = min(suf[k + 1], dp[i][j][k]);
				for (int k = 1; k <= m; ++k) 
					f[i][j][k] = min(pre[k - 1], suf[k + 1]);
				// dbg(i, j, dp[i][j], f[i][j]);
			}
		}
		int ans = -1;
		for (int i = 1; i <= m; ++i) {
			if (dp[n][target][i] != 0x3f3f3f3f) {
				if (ans == -1) ans = dp[n][target][i];
				else ans = min(ans, dp[n][target][i]);
			}
		}
		return ans;
	}
};