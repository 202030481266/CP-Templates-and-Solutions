// https://leetcode.cn/problems/make-array-strictly-increasing/
// 二分查找 + 排序 + 动态规划 + 贪心


class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    	// arr2中的一个数字只有可能被替换一次，那么对于每个数字来说可以替换和不替换，替换代价+1
    	// 构建图的模型似乎是可行的，但是非常复杂，感觉还是动态规划问题，即在状态搜索图上规划。
    	// 似乎每一次替换尾部都应该使用最小的数字，然后一直往后替换直到前面的数字大于现在的？（贪心）
    	sort(arr2.begin(), arr2.end());
    	arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());  // 去重
		int n = arr1.size(), m = arr2.size(), dp[n + 1][m + 1];
    	memset(dp, -1, sizeof(dp));
    	// dfs
    	function<int(int, int)> dfs = [&](int i, int j) -> int {
    		int &res = dp[i][j];
    		if (i >= n - 1) return 0;  // 匹配到了n-1并且是合法的
    		if (res != -1) return res;
    		// 没有可以替换的元素
    		if (j == m) return res = (is_sorted(arr1.begin() + i, arr1.end()) ? 0 : 0x3f3f3f3f);
    		res = 0x3f3f3f3f;  // 表示无解
    		// 替换第i个数字，那么根据贪心的法则，一定要替换最小的那个数字
			int cost = 1, pre = arr2[j], p = i + 1, q = j + 1;
			while (p < n && arr1[p] <= pre && q < m) pre = arr2[q++], ++p, ++cost;
			if ((p < n && arr1[p] > pre) || p == n) res = min(res, cost + dfs(p, q));
			// 不替换第i个数字
			cost = 0, pre = arr1[i], p = i + 1, q = (upper_bound(arr2.begin() + j, arr2.end(), arr1[i]) - arr2.begin());
			while (p < n && arr1[p] <= pre && q < m) pre = arr2[q++], ++p, ++cost;
			if ((p < n && arr1[p] > pre) || p == n) res = min(res, cost + dfs(p, q));
    		return res;
    	};
    	return dfs(0, 0) == 0x3f3f3f3f ? -1 : dfs(0, 0);
    }