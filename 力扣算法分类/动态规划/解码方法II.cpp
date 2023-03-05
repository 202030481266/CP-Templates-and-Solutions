// https://leetcode.cn/problems/decode-ways-ii/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int numDecodings(string S) {
    	int n = S.size();
    	string s = " " + S;

    	vector<long long> dp(n + 1);
    	dp[0] = 1;

    	for (int i = 1; i <= n; ++i) {
    		if (isdigit(s[i])) {
    			// only use the s[i]
    			if (s[i] != '0') {
    				dp[i] = dp[i - 1];
    			}
    			// combine the prev one
    			if (i > 1) {
    				if (isdigit(s[i - 1]) && s[i - 1] != '0' && (s[i - 1] - '0') * 10 + (s[i] - '0') <= 26)
    					dp[i] = (dp[i] + dp[i - 2]) % mod;
    				else if (s[i - 1] == '*') {
    					// can get multi type of encodings
    					if (s[i] - '0' <= 6) {
    						// * can be 1, 2
    						dp[i] = (dp[i] + dp[i - 2] * 2) % mod;
    					}
    					else {
    						// * can only can be 1
    						dp[i] = (dp[i] + dp[i - 2]) % mod;
    					}
    				}
    			}
    		}
    		else {
    			// s[i] == '*'
    			// only use the s[i]
    			dp[i] = (dp[i - 1] * 9) % mod;
    			// combine the prev one
    			if (i > 1) {
    				if (isdigit(s[i - 1])) {
    					// s[i - 1] should be 1 or 2
    					if (s[i - 1] == '1') {
    						// * can be 1 ~ 9
    						dp[i] = (dp[i] + dp[i - 2] * 9) % mod;
    					}
    					if (s[i - 1] == '2') {
    						// * can be 1 ~ 6
    						dp[i] = (dp[i] + dp[i - 2] * 6) % mod;
    					}
    				}
    				else if (s[i - 1] == '*') {
    					// s[i - 1] is '*'
    					dp[i] = (dp[i] + dp[i - 2] * 15) % mod;
    				}
    			}
    		}
    	}
    	return dp[n];
    }
};