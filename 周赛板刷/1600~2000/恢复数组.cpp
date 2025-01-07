// https://leetcode.cn/problems/restore-the-array/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int numberOfArrays(string s, int k) {
    	int n = s.size();
    	string sk = to_string(k);
    	int m = sk.size();


    	vector<long long> dp(n + 1);
    	vector<long long> utils{
    		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
    	};

    	dp[0] = 1;
    	for (int i = 1; i <= n; ++i) {
    		long long t = 0;
    		int j = 1;
    		while (i - j >= 0 && t <= k && j <= m) {
    			t += (s[i - j] - '0') * utils[j - 1]; 
    			if (t > k) break;
    			if (s[i - j] - '0' > 0 && t > 0) dp[i] = (dp[i] + dp[i - j]) % mod;
    			++j;
    		}
    	}
    	return dp[n];
    }
};