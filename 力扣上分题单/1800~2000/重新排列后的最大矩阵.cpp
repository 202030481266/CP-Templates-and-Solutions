// https://leetcode.cn/problems/largest-submatrix-with-rearrangements/



class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
    	int n = matrix.size(), m = matrix[0].size();

    	vector dp(n + 1, vector<int>(m + 1, 0));

    	int ans = 0;
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 1; j <= m; ++j) {
    			if (!matrix[i - 1][j - 1]) dp[i][j] = 0;
    			else dp[i][j] = dp[i - 1][j] + 1;
    		}
    		vector<int> temp(dp[i].begin(), dp[i].end());
    		sort(temp.begin(), temp.end());
    		for (int j = m; j >= 1; --j) {
    			if (temp[j] == 0) break;
    			ans = max(ans, temp[j] * (m - j + 1));
    		}
    	}
    	return ans;
    }
};