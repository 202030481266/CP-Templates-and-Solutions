// https://leetcode.cn/problems/last-stone-weight-ii/
// 题解分析的很好： https://leetcode.cn/problems/last-stone-weight-ii/solutions/818362/gong-shui-san-xie-xiang-jie-wei-he-neng-jgxik/


class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
    	int n = stones.size();

    	// 分成两堆石子，一个是负号堆，一个是正号堆
    	// 尽量把石子平均分
    	// 等价于 01 背包中选择总和不超过 sum/2 的最大价值

    	int s = accumulate(stones.begin(), stones.end(), 0);
    	int m = s / 2;
    	vector<int> dp(m + 1);
    	for (int i = 0; i < n; ++i)
    		for (int j = m; j >= stones[i]; --j)
    			dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
    	return abs(s - dp[m] * 2);
    }
};