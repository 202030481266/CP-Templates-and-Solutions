// https://leetcode.cn/problems/sum-of-floored-pairs/



class Solution {
public:
	static constexpr int mod = 1000000007;
	long long sum[100001];
    int sumOfFlooredPairs(vector<int>& nums) {
    	// 关键点1： 1 <= nums[i] <= 100000 （可以做前缀和计算）
    	// 只有分子大于等于分母的时候才有意义, 统计谁？统计分子贡献？统计分母贡献？
    	// 关键点2：统计分母贡献需要枚举分母的倍数来获得贡献区间，但是枚举倍数的时间复杂度有点高把（第一印象）
    	// 关键点3：仔细观察，对于每一个数字，枚举的倍数都是至少减少两倍！那么这就是调和级数的复杂度了(ClogC)
    	int n = nums.size(), mx = 0;
    	memset(sum, 0, sizeof(sum));
    	for (int &c : nums) ++sum[c], mx = max(mx, c);
    	for (int i = 1; i <= mx; ++i) sum[i] += sum[i - 1];
    	long long ans = 0;
    	for (int i = 1; i <= mx; ++i) {
    		// 考虑对于数字i的贡献
    		if (sum[i] - sum[i - 1] == 0) continue;
    		for (int j = 1; j * i <= mx; ++j) {
    			int left = j * i, right = (j + 1) * i - 1;
    			if (right >= mx) ans = (ans + (sum[i] - sum[i - 1]) * (sum[mx] - sum[left - 1]) * j % mod) % mod;
    			else ans = (ans + (sum[i] - sum[i - 1]) * (sum[right] - sum[left - 1]) * j % mod) % mod;
    		}
    	}
    	return ans;
    }
};