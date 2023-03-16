// https://leetcode.cn/problems/maximum-repeating-substring/



class Solution {
public:
    int maxRepeating(string sequence, string word) {
    	int n = sequence.size(), m = word.size();
    	vector<int> dp(n + 1, 0);

    	if (n < m) return 0;

    	for (int i = m - 1; i < n; ++i) {
    		int j = i - m + 1;
    		if (sequence.substr(j, m) == word)
    			dp[i + 1] = dp[j] + 1;
    	}
    	int ans = 0;
    	for (int i = 1; i <= n; ++i)
    		ans = max(ans, dp[i]);
    	return ans;
    }
};