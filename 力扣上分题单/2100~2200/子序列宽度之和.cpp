// https://leetcode.cn/problems/sum-of-subsequence-widths/



int cnt[100010], sum[100010];
class Solution {
public:
	static constexpr int mod = 1000000007;
	long long pow_mod(int x, int n) {
	    long long res = 1;
	    for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
	        if ((n & 1) != 0)
	            res = (int)(res * p % mod);
	    return res;
	}
	long long cal(int x, int n) {
		return (pow_mod(x, n) - 1 + mod) % mod;
	}
    int sumSubseqWidths(vector<int>& nums) {
    	// 1 <= nums[i] <= 1e5
    	// 数学题目，容斥原理 + 排序 + 组合数学
    	// 关键点：答案的统计和子序列中的数字顺序是无关的
    	memset(cnt, 0, sizeof(cnt));
    	memset(sum, 0, sizeof(sum));
    	int n = nums.size(), pos = 0, neg = 0;
    	for (int i = 0; i < n; ++i) ++cnt[nums[i]];
    	for (int i = 1; i <= 100000; ++i) sum[i] = sum[i - 1] + cnt[i];
    	for (int i = 1; i <= 100000; ++i) {
    		if (cnt[i] == 0) continue;
    		// 统计作为最大值的贡献
    		pos = (pos + i * cal(2, sum[i - 1]) % mod * cal(2, cnt[i]) % mod) % mod;
    		// 统计作为最小值的贡献
    		neg = (neg + i * cal(2, n - sum[i]) % mod * cal(2, cnt[i]) % mod) % mod;
    	}
    	return (pos - neg + mod) % mod;
    }
};