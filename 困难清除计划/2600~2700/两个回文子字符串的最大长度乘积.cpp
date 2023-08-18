// 回文串长度为奇数就是为了方便使用manacher
class Solution {
public:
    long long maxProduct(string s) {
    	int n = s.size();
    	vector<int> dp(n);
    	vector<int> pre(n, 1), suf(n, 1);
    	for (int i = 0, l = 0, r = -1; i < n; ++i) {
    		int k = (i > r) ? 1 : min(r - i + 1, dp[l + r - i]);
    		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
    			pre[i + k] = max(pre[i + k], k + 1);
					++k;
    		} 
    		dp[i] = k--; 
    		if (i + k > r) l = i - k, r = i + k;
    	}
    	fill(dp.begin(), dp.end(), 0);
    	for (int i = n - 1, l = n - 1, r = n; i >= 0; --i) {
    		int k = (i < r) ? 1 : min(i - r + 1, dp[l + r - i]);
    		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
    			suf[i - k] = max(suf[i - k], k + 1);
					++k;
    		}
    		dp[i] = k--;
    		if (i - k < r) l = i + k, r = i - k;
    	}
    	for (int i = 1; i < n; ++i) pre[i] = max(pre[i - 1], pre[i]);
    	for (int i = n - 2; i >= 0; --i) suf[i] = max(suf[i + 1], suf[i]);
    	long long ans = 0;
    	for (int i = 0; i < n - 1; ++i) {
    		long long x = 2 * pre[i] - 1, y = 2 * suf[i + 1] - 1;
    		ans = max(ans, x * y);
    	}
    	return ans;
    }
};