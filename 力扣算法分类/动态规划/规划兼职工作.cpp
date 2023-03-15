// https://leetcode.cn/problems/maximum-profit-in-job-scheduling/



class Solution {
public:
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		vector<vector<int>> a;

		for (int i = 0; i < profit.size(); ++i) {
			a.emplace_back(vector<int>{ startTime[i], endTime[i], profit[i] });
		}
		sort(a.begin(), a.end(), [&](const vector<int>& x, const vector<int>& y) {
			return  (x[1] == y[1]) ? (x[0] < y[0]) : (x[1] < y[1]);
			});
		int n = a.size();

		vector<int> b;
		vector dp(n, vector<int>(2));

		dp[0][1] = a[0][2];
		dp[0][0] = 0;
		b.emplace_back(a[0][1]);
		for (int i = 1; i < n; ++i) {
			dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
			dp[i][1] = a[i][2];
			auto it = upper_bound(b.begin(), b.end(), a[i][0]);
			if (it != b.begin()) {
				// means can find a endtime that satisfy t <= a[i][0]
				int pos = it - b.begin() - 1;
				dp[i][1] = max(dp[i][1], max(dp[pos][1], dp[pos][0]) + a[i][2]);
			}
			b.emplace_back(a[i][1]);
		}
		/*for (int i = 0; i < n; ++i)
			printf("job%d start from %d to %d and profit is %d\n", i, a[i][0], a[i][1], a[i][2]);

		for (int i = 0; i < n; ++i) {
			printf("dp[%d][0] = %d, dp[%d][1] = %d\n", i, dp[i][0], i, dp[i][1]);
		}*/
		return max(dp[n - 1][1], dp[n - 1][0]);
	}
};