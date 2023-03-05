// https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
// dp[a] 表示字符a结尾的最大匹配子串
// 结尾字符固定然后通过长度可以唯一确定一个子串



class Solution {
public:
    int findSubstringInWraproundString(string s) {
    	int n = s.size();
    	vector<int> dp(n);

    	dp[0] = 1;

    	for (int i = 1; i < n; ++i) {
    		dp[i] = 1;
    		int x = s[i] - 'a', y = s[i - 1] - 'a';
    		if (y == (x + 25) % 26) {
    			dp[i] = max(dp[i - 1] + 1, dp[i]);
    		}
    	}
    	vector<int> cnt(26);
        int ans = 0;
    	for (int i = 0; i < n; ++i)
    		cnt[s[i] - 'a'] = max(cnt[s[i] - 'a'], dp[i]);
    	for (int i = 0; i < 26; ++i)
    		ans += cnt[i];
    	return ans;
    }
};