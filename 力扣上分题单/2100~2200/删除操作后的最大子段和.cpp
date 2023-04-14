// https://leetcode.cn/problems/maximum-segment-sum-after-removals/




class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
    	int m = removeQueries.size(), n = nums.size(), vis[n], fa[n];
    	vector<long long> ans(m), sum(n);
    	// 动态维护最大子段和
    	// 关键信息1：查询的分割点的大小和数组大小一样
    	// 关键信息2：每一次的分割点都不一样。
    	// 逆向思维：从后面开始倒着开始，每一次放进一个新的数字，更新答案，转换为区间合并问题
    	memset(vis, 0, sizeof(vis));
    	for (int i = 0; i < n; ++i) fa[i] = i;
    	function<int(int)> find = [&](int x) -> int { return fa[x] == x ? x : fa[x] = find(fa[x]); };
    	function<void(int, int)> merge = [&](int x, int y) {
    		int f1 = find(x), f2 = find(y);
    		if (f1 != f2) fa[f2] = f1, sum[f1] += sum[f2], sum[f2] = 0;
    	};
    	long long mx = INT_MIN;
    	for (int i = m - 1; i >= 1; --i) {
    		int pos = removeQueries[i];
    		vis[pos] = true;
    		sum[pos] = nums[pos];
    		if (pos > 0 && vis[pos - 1]) merge(pos, pos - 1);
    		if (pos < n - 1 && vis[pos + 1]) merge(pos, pos + 1);
    		mx = max(mx, sum[find(pos)]);
    		ans[i - 1] = mx;
    	}
    	return ans;
    }
};