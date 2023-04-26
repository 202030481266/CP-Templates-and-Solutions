// https://leetcode.cn/problems/make-sum-divisible-by-p/



class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
    	int n = nums.size();
    	vector<int> sum(n + 1); 

    	for (int i = 1; i <= n; ++i)
    		sum[i] = (sum[i - 1] + nums[i - 1]) % p;
    	if (sum[n] == 0) return 0;

    	int c = sum[n];
    	int ans = INT_MAX;
    	unordered_map<int, int> h;
    	h[0] = 0;
    	for (int i = 1; i <= n; ++i) {
    		int a = sum[i];
    		h[a] = i;
    		if (h.count(a - c)) ans = min(ans, i - h[a - c]);
    		if (h.count(p - c + a)) ans = min(ans, i - h[p - c + a]);
    	}
    	return ans == n ? -1 : ans;
    }
};