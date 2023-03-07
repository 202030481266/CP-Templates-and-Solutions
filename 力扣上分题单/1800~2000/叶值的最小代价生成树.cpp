// https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/



class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
    	int n = arr.size();

    	vector f(n, vector<int>(n));
    	for (int i = 0; i < n; ++i) {
    		f[i][i] = arr[i];
    		for (int j = i + 1; j < n; ++j) 
    			f[i][j] = max(f[i][j - 1], arr[j]);
    	}
    	vector g(n, vector<int>(n, -1));

    	function<int(int,int)> dfs = [&](int l, int r) -> int {
    		if (l == r) return 0;
    		if (g[l][r] != -1) return g[l][r];
    		int temp = INT_MAX;
    		for (int i = l; i < r; ++i) 
    			temp = min(temp, dfs(l, i) + dfs(i + 1, r) + f[l][i] * f[i + 1][r]);
    		return g[l][r] = temp;
    	};
    	return dfs(0, n - 1);
    }
};