// https://leetcode.cn/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int numWays(vector<string>& words, string target) {
    	int n = words[0].size();
    	int N = words.size();
    	int m = target.size();

    	vector a(26, vector<int>(n + 1, 0)); // a[0][i] means numbers of the 'a' can be match at index i 

    	for (string w : words) {
    		for (int i = 0; i < n; ++i) {
    			++a[w[i] - 'a'][i + 1];
    		}
    	}

    	vector dp(2, vector<long long>(n + 1, 0));
    	vector sum(2, vector<long long>(n + 1, 0));
    	// use no character to match empty string is 1
    	dp[0][0] = 1;
    	for (int i = 0; i <= n; ++i) sum[0][i] = 1;
    	// start update at cur
    	int cur = 1;

    	for (int i = 1; i <= m; ++i) {
    		for (int j = 1; j <= n; ++j) {
    			if (a[target[i - 1] - 'a'][j]) {
	    			dp[cur][j] = sum[cur ^ 1][j - 1];
	    			dp[cur][j] = (dp[cur][j] * a[target[i - 1] - 'a'][j]) % mod;
	    		}
    		}
    		sum[cur][0] = dp[cur][0];
    		for (int j = 1; j <= n; ++j) {
    			sum[cur][j] = (sum[cur][j - 1] + dp[cur][j]) % mod;
    		}
    		cur ^= 1;
            fill(dp[cur].begin(), dp[cur].end(), 0);
            fill(sum[cur].begin(), sum[cur].end(), 0);
    	}

    	long long ans = 0;
    	for (int i = 1; i <= n; ++i) ans = (ans + dp[cur ^ 1][i]) % mod;
    	return ans;
    }
};