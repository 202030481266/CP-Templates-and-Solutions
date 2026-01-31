//https://leetcode.cn/problems/minimum-total-space-wasted-with-k-resizing-operations/


typedef long long ll;
class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
    	ll n = nums.size(), dp[n + 1][k + 2], s[n + 1], mx[n + 1][n + 1];
    	memset(dp, 0x3f, sizeof(dp));
    	memset(s, 0, sizeof(s));
    	memset(mx, 0, sizeof(mx));
    	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + nums[i - 1];
    	for (int i = 1; i <= n; ++i)
    		for (int j = i; j <= n; ++j) 
    			mx[i][j] = max(mx[i][j - 1], 1ll*nums[j - 1]);
    	dp[0][0] = 0;
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 1; j <= min(k + 1, i); ++j) {
    			for (int x = j; x <= i; ++x) {
    				// [x...i] is the j segment
    				ll cost = mx[x][i] * (i - x + 1) - s[i] + s[x - 1];
    				dp[i][j] = min(dp[i][j], dp[x - 1][j - 1] + cost);
    			}
    		}
    	}
    	return *min_element(dp[n], dp[n] + k + 2);
    }
};