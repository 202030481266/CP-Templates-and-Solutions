// https://leetcode.cn/problems/minimum-xor-sum-of-two-arrays/



class Solution {
public:
	typedef long long ll;
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
    	// 1<= n <= 14 看起来是爆搜的问题
        // 阶乘复杂度卡了，所以转换为2^n的问题
    	ll n = nums1.size(), dp[1 << n][n];
    	memset(dp, -1, sizeof(dp));

    	function<ll(int, int)> dfs = [&](int s, int d) -> ll {
    		if (d == n) return 0;
    		ll &res = dp[s][d];
    		if (res != -1) return dp[s][d];
    		res = INT_MAX;
    		for (int i = 0; i < n; ++i) 
    			if ((s >> i) & 1)  
                    // 注意这里的异或操作的优先级，特别容易出错
    				res = min(res, (nums1[d] ^ nums2[i]) + dfs(s ^ (1 << i), d + 1));
    		return res;
    	};
        return dfs((1 << n) - 1, 0);
    }
};