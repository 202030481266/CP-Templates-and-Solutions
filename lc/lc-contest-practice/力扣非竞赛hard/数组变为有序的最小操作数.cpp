// 单调队列
static int dp[1010][1001];
class Solution {
public:
    int convertArray(vector<int>& nums) {
        int n = nums.size(), ans = INT_MAX;
		auto f = [&]() {
			memset(dp, 0, sizeof(dp));
			for (int i = 1; i <= n; ++i) {
				for (int j = 0, res = dp[i - 1][0]; j <= 1000; ++j) {
					// dp[i][j] = min{dp[i - 1][x]} + abs(j - nums[i - 1]);
					// x <= j;
					res = min(res, dp[i - 1][j]);
					dp[i][j] = res + abs(j - nums[i - 1]);
				}
			}
			for (int i = 0; i <= 1000; ++i) ans = min(ans, dp[n][i]);
		};
		f();
        reverse(nums.begin(), nums.end());
		f();
		return ans;
    }
};


