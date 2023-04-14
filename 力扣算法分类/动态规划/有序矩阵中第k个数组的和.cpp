// https://leetcode.cn/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/



class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
    	int n = mat.size(), m = mat[0].size(), s[n + 1];
    	int cnt = 0, sum = 0, v;
    	memset(s, 0, sizeof(s));

    	// 提供优化剪枝的前缀和
    	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + mat[i - 1][0];

    	function<void(int)> dfs = [&](int d) {
    		if (sum > v || cnt > k) return; //最优化剪枝
    		if (d == n) {
    			++cnt;
    			return;
    		}
    		// d到n-1层无论怎么取都不行
    		if (s[n] - s[d] + sum > v) return;
    		for (int i = 0; i < m; ++i) {
    			if (sum + mat[d][i] > v) break;  //可行性剪枝
    			sum += mat[d][i];
    			dfs(d + 1);
    			sum -= mat[d][i];
    		}
    	};

    	int l = 0, r = 0, ans = 0;
    	for (int i = 0; i < n; ++i) l += mat[i][0], r += mat[i].back();
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		cnt = sum = 0, v = mid;
    		dfs(0);
    		if (cnt >= k) ans = v, r = mid - 1; 
    		else if (cnt < k) l = mid + 1;
    	}
    	return ans;
    }
};