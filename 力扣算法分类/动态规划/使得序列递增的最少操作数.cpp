// https://leetcode.cn/problems/minimum-swaps-to-make-sequences-increasing/
// 由于影响后面判断决策的就是最后一个数字，所以可以进行轮廓线规划


class Solution {
public:
	int minSwap(vector<int>& a, vector<int>& b) {
		int n = a.size();
		vector dp(n + 1, vector<int>(2, INT_MAX / 2));

		dp[0][0] = 0;
		dp[0][1] = 1;
		for (int i = 1; i < n; ++i) {
			if (a[i] > a[i - 1] && b[i] > b[i - 1]) {
				dp[i][0] = min(dp[i][0], dp[i - 1][0]);
				dp[i][1] = min(dp[i][1], dp[i - 1][1] + 1);
			}
			if (a[i] > b[i - 1] && b[i] > a[i - 1]) {
				dp[i][0] = min(dp[i][0], dp[i - 1][1]);
				dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
			}
			if (a[i] <= a[i - 1] || b[i] <= b[i - 1]) {
				dp[i][0] = min({ dp[i][0], dp[i - 1][1] });
				dp[i][1] = min({ dp[i][1], dp[i - 1][0] + 1 });
			}
		}
		return min(dp[n - 1][0], dp[n - 1][1]);
	}
};

