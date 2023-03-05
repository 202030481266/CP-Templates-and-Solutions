// https://leetcode.cn/problems/minimum-number-of-removals-to-make-mountain-array/



class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
    	int n = nums.size();

    	vector<int> f(n + 1, 0);
    	vector<int> t(n + 1, 0);
    	vector<int> g(n + 1, INT_MAX);

    	for (int i = 0; i < n; ++i) {
    		int j = lower_bound(g.begin(), g.end(), nums[i]) - g.begin();
    		f[i] = j + 1;
    		g[j] = nums[i];
    	}
    	fill(g.begin(), g.end(), INT_MAX);
    	for (int i = n - 1; i >= 0; --i) {
    		int j = lower_bound(g.begin(), g.end(), nums[i]) - g.begin();
    		t[i] = j + 1;
    		g[j] = nums[i];
    	}

    	int ans = INT_MAX;
    	for (int i = 1; i < n - 1; i++) {
    		// 0 ~ i
    		int x = (i + 1) - f[i];
    		// i ~ n - 1
    		int y = (n - i) - t[i];
    		// should not be the first one or last one
    		if (x == i || y == (n - i - 1)) continue;
    		ans = min(ans, x + y);
    	}
    	return ans;
    }
};