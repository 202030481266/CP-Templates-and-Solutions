// https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/
// 逆向思维 + dp
// 石子合并的问题


class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
    	int m = cuts.size();
    	// sort
    	sort(cuts.begin(), cuts.end());

    	// add piles
    	vector<int> a;
    	a.emplace_back(cuts[0]);
    	for (int i = 1; i < m; ++i) {
    		a.emplace_back(cuts[i] - cuts[i - 1]);
    	}
    	a.emplace_back(n - cuts.back());

    	// 0 ~ m is the pile
    	vector dp(m + 1, vector<int>(m + 1, INT_MAX / 2));
    	vector<int> sum(m + 2, 0);
    	for (int i = 1; i <= m + 1; ++i) sum[i] = sum[i - 1] + a[i - 1];
    	for (int i = 0; i <= m; ++i) dp[i][i] = 0;
    	for (int len = 2; len <= m + 1; ++len) {
    		for (int i = 0; i + len - 1 <= m; ++i) {
    			int j = i + len - 1;
    			for (int k = i; k < j; ++k) {
    				// [i, k] and [k + 1, j]
    				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum[j + 1] - sum[i]);
    			}
    		}
    	}
    	return dp[0][m];
    }
};