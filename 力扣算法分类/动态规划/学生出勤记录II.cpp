// https://leetcode.cn/problems/student-attendance-record-ii/



class Solution {
public:
	static constexpr int mod = 1e9 + 7;
	int checkRecord(int n) {
		vector dp(n + 1, vector(3, vector<long long>(2, 0)));
		dp[1][0][1] = 1; // A
		dp[1][1][0] = 1; // L
		dp[1][0][0] = 1; // P
		for (int i = 2; i <= n; ++i) {
			dp[i][0][0] = (dp[i - 1][0][0] + dp[i - 1][1][0] + dp[i - 1][2][0]) % mod;
			dp[i][0][1] = (dp[i - 1][0][1] + dp[i - 1][1][1] + dp[i - 1][2][1] + dp[i][0][0]) % mod;
			dp[i][1][0] = dp[i - 1][0][0];
			dp[i][1][1] = dp[i - 1][0][1];
			dp[i][2][0] = dp[i - 1][1][0];
			dp[i][2][1] = dp[i - 1][1][1];
		}
		long long ans = 0;
		for (int i = 0; i < 3; ++i) ans = (ans + dp[n][i][0] + dp[n][i][1]) % mod;

		// dbg(ans);

		return ans;
	}
};