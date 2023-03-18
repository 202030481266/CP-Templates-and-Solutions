// https://leetcode.cn/problems/minimum-number-of-work-sessions-to-finish-the-tasks/
// 非常牛逼的技巧，使用了一种叫做子集规划的技术


class Solution {
public:
	int minSessions(vector<int>& tasks, int sessionTime) {
		int n = tasks.size();
		int N = (1 << n);

		vector<int> dp(N, 0x3f3f3f3f);
		vector<bool> f(N, false);
		f[0] = true;
		for (int i = 1; i < N; ++i) {
			int sum = 0;
			for (int j = 0; j < n; ++j) {
				if ((i >> j) & 1) {
					sum += tasks[j];
				}
			}
			if (sum <= sessionTime) f[i] = true;
		}
		dp[0] = 0;
		for (int i = 1; i < N; ++i) {
			for (int s = i; s; s = (s - 1) & i) {
				if (f[s])
					dp[i] = min(dp[i], dp[i ^ s] + 1);
			}
		}
		return dp[N - 1];
	}
};