// https://leetcode.cn/problems/ones-and-zeroes/



class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
    	vector<vector<int>> a;
    	for (auto c : strs) {
    		int cnt1 = 0, cnt0 = 0;
    		for (auto p : c) {
    			if (p == '1') ++cnt1;
    			else ++cnt0;
    		}
    		a.emplace_back(vector<int>{cnt0, cnt1});
    	}
    	vector dp(m + 1, vector<int>(n + 1));
    	for (int i = 0; i < a.size(); ++i) {
    		for (int j = m; j >= a[i][0]; --j)
    			for (int k = n; k >= a[i][1]; --k)
    				dp[j][k] = max(dp[j][k], dp[j - a[i][0]][k - a[i][1]] + 1);
        }
    	return dp[m][n];
    }
};