// https://leetcode.cn/problems/minimize-the-difference-between-target-and-chosen-elements/
// 分组背包 + 值域优化


class Solution {
public:
	int minimizeTheDifference(vector<vector<int>>& mat, int target) {
		int n = mat.size(), m = mat[0].size();
		// 经典分组背包问题
		vector dp(2, vector<bool>(target));
		int cur = 0;
		dp[cur][0] = true;
		int large = INT_MAX;
		for (int i = 0; i < n; ++i) {
			int t = INT_MAX;
			for (int x : mat[i]) {
				for (int j = 0; j < target; ++j) {
					if (dp[cur][j]) {
						if (j + x >= target) {
							t = min(t, j + x);
						}
						else {
							dp[cur ^ 1][j + x] = true;
						}
					}
				}
				if (large != INT_MAX) {
					// 防止t为INT_MAX
					t = min(large + x, t);
				}
			}
            fill(dp[cur].begin(), dp[cur].end(), false);
			cur ^= 1;
			large = t;
		}
		int ans = large - target;
		for (int i = target - 1; i >= 1; --i) {
			if (dp[cur][i]) {
				ans = min(ans, target - i);
				break;
			}
		}
		return ans;
	}
};
