// https://leetcode.cn/problems/fair-distribution-of-cookies/



class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
    	int n = cookies.size(), f[1 << n][k + 1], sum[1 << n];
    	memset(f, 0x3f, sizeof(f));
    	memset(sum, 0, sizeof(sum));

    	for (int i = 0; i < (1 << n); ++i) {
    		for (int j = 0; j < n; ++j)
    			if ((i >> j) & 1) sum[i] += cookies[j];
    	}

    	f[0][0] = 0;
    	// f[i][k] = min(max(f[i ^ s][k - 1], sum[s]))
    	for (int i = 0; i < (1 << n); ++i) {
    		for (int j = 1; j <= k; ++j) {
    			// 枚举子集
    			for (int s = i; s > 0; s = (s - 1) & i) {
    				f[i][j] = min(f[i][j], max(f[i ^ s][j - 1], sum[s]));
    			}
    		}
    	}
    	return f[(1 << n) - 1][k];
    }
};