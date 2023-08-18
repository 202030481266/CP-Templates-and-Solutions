// https://leetcode.cn/problems/maximum-number-of-ways-to-partition-an-array/



class Solution {
public:
	typedef long long ll;
    int waysToPartition(vector<int>& nums, int k) {
    	ll n = nums.size(), pre[n + 2], suf[n + 2], con[n + 1];
    	unordered_map<int, int> cnt1, cnt2;
    	memset(pre, 0, sizeof(pre)); 
    	memset(suf, 0, sizeof(suf));
    	memset(con, 0, sizeof(con));
    	for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + nums[i - 1];
    	for (int i = n; i >= 1; --i) suf[i] = suf[i + 1] + nums[i - 1];
    	for (int i = n - 1; i >= 1; --i) {
    		++cnt1[2 * pre[i]];
    		con[i] += cnt1[pre[n] + nums[i - 1] - k];
    	}
    	for (int i = 2; i <= n; ++i) {
    		++cnt2[2 * suf[i]];
    		con[i] += cnt2[suf[1] + nums[i - 1] - k];
    	}
    	ll ans = 0, mx = 0, idx = -1, res = 0, a, b;
    	for (int i = 1; i <= n - 1; ++i) 
    		if (pre[i] == suf[i + 1]) ++ans;
    	for (int i = 1; i <= n; ++i) 
    		if (con[i] > mx && nums[i - 1] != k) mx = con[i], idx = i; // 如果是k的话修改没有意义
    	if (idx == -1) return ans;
    	a = 0, b = pre[n] - nums[idx - 1] + k; 
    	nums[idx - 1] = k;
    	for (int i = 0; i < n - 1; ++i) {
    		a += nums[i], b -= nums[i];
    		if (a == b) ++res;
    	}
    	return max(res, ans);
    }
};