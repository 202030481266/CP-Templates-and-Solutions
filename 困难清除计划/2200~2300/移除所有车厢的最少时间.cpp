// https://leetcode.cn/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/



class Solution {
public:
    int minimumTime(string s) {
    	int n = s.size(), pre[n + 2], suf[n + 2];
    	memset(pre, 0x3f, sizeof(pre));
    	memset(suf, 0x3f, sizeof(suf));
    	for (int i = 1; i <= n; ++i) {
    		if (s[i - 1] == '1')
    			pre[i] = min(pre[i - 1] + 2, i);
    		else pre[i] = pre[i - 1];
    	}
    	for (int i = n; i >= 1; --i)  {
    		if (s[i - 1] == '1')
    			suf[i] = min(suf[i + 1] + 2, n - i + 1);
    		else suf[i] = suf[i + 1];
    	}
    	int ans = INT_MAX;
    	for (int i = 1; i <= n; ++i)
    		ans = min(ans, pre[i] + suf[i + 1]);
    	return ans;
    }
};