// https://leetcode.cn/problems/split-array-with-same-average/



// 动态规划的复杂度比较高，过不了，有点离谱
class Solution {
public:
	bool splitArraySameAverage(vector<int>& nums) {
		int n = nums.size(), sum = 0;
		for (auto c : nums) sum += c;

		vector dp(sum + 1, vector<bool>(n));
		dp[0][0] = true;
		for (int i = 0; i < n; ++i) {
			for (int j = n - 1; j >= 1; --j) {
				for (int s = sum; s >= nums[i]; --s)
					dp[s][j] = (dp[s][j] || dp[s - nums[i]][j - 1]);
			}
		}
		for (int j = 1; j < n; ++j)
			for (int s = 1; s <= sum; ++s)
				if (n * s == j * sum && dp[s][j]) return true;
		return false;
	}
};


// 折半搜索，将数组分为两个部分，这样的话可以达到 2^(n / 2) 的复杂度，减少了很多，因此可以直接枚举子集
// 先将所有的数字减去平均值然后转换为从集合中选取一些数字使得它们的和为0
class Solution {
public:
    bool splitArraySameAverage(vector<int> &nums) {
        int n = nums.size(), m = n / 2;
        if (n == 1) {
            return false;
        }

        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (int &x : nums) {
            x = x * n - sum;
        }

        unordered_set<int> left;
        for (int i = 1; i < (1 << m); i++) {
            int tot = 0;
            for (int j = 0; j < m; j++) {
                if (i & (1 << j)) {
                    tot += nums[j];
                }
            }
            if (tot == 0) {
                return true;
            }
            left.emplace(tot);
        }

        int rsum = accumulate(nums.begin() + m, nums.end(), 0);
        for (int i = 1; i < (1 << (n - m)); i++) {
            int tot = 0;
            for (int j = m; j < n; j++) {
                if (i & (1 << (j - m))) {
                    tot += nums[j];
                }
            }
            if (tot == 0 || (rsum != tot && left.count(-tot))) {
                return true;
            }
        }
        return false;
    }
};

