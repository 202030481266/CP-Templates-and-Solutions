// https://leetcode.cn/problems/maximum-height-by-stacking-cuboids/description/
/*
	1、对其中一个维度进行排序后就可以转换为最长上升子序列的问题
*/
// 模板1 堆箱子的问题
class Solution {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
    	int n = cuboids.size(), dp[n];
    	memset(dp, 0, sizeof(dp));
    	for (auto &c : cuboids) sort(c.begin(), c.end()); // 排序，可以把最长的边直接看做高
    	sort(cuboids.begin(), cuboids.end());
    	// dp
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < i; ++j)
    			if (cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2])
    				dp[i] = max(dp[i], dp[j]);
    		dp[i] += cuboids[i][2];
    	}
    	return *max_element(dp, dp + n);
    }
};
// 信封问题
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty()) return 0;
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);  // 注意这里的细节，相同的话逆序排列，这样可以保证不回取到相同宽度的信封
        });
        vector<int> f = {envelopes[0][1]};
        for (int i = 1; i < n; ++i) {
            if (int num = envelopes[i][1]; num > f.back()) {
                f.push_back(num);
            }
            else {
                auto it = lower_bound(f.begin(), f.end(), num);
                *it = num;
            }
        }
        return f.size();
    }
};


// 快速版本LIS
class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        vector<int> g;
        for (int x : nums) {
            auto it = lower_bound(g.begin(), g.end(), x);
            if (it == g.end()) g.push_back(x); // >=x 的 g[j] 不存在
            else *it = x;
        }
        return g.size();
    }
};

