// https://leetcode.cn/problems/minimum-white-tiles-after-covering-with-carpets/



// 暴力过不了
class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
    	int n = floor.size();
    	vector<int> sum(n + 1);

    	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (floor[i - 1] == '1');

    	// dp[i][k] means use at most k carpets to overlap the [i...n] and the remain white floors
    	vector dp(n + 1, vector<int>(numCarpets + 1, -1));

    	function<int(int, int)> dfs = [&](int i, int k) -> int {
    		int &res = dp[i][k];
    		if (res != -1) return res;

    		if (carpetLen * k >= (n - i + 1)) return res = 0;

    		res = INT_MAX;
    		int ones = 0;

    		for (int j = i; j <= n; ++j) {
    			if (floor[j - 1] == '1') {
    				++ones;
    				if (k > 0) {
    					// [i.. j-1] + dfs(min(j + len, n), k - 1)
    					// [j, j + len - 1] is overlap
    					if (j + carpetLen > n) res = min(res, sum[j - 1] - sum[i - 1]);
    					else res = min(res, sum[j - 1] - sum[i - 1] + dfs(j + carpetLen, k - 1));
    				}
    			}
    		}
    		// have no carpets
    		if (res == INT_MAX) return res = ones;
    		return res;
    	};
    	return dfs(1, numCarpets);
    }
};


// 考虑使用第i条地毯是否覆盖来第j个格子，非常简单并且改变了状态设计之后很直观
// 经典序列DP
class Solution {
public:
    int minimumWhiteTiles(string &floor, int n, int carpetLen) { 
        int m = floor.length();
        if (n * carpetLen >= m) return 0; // 剪枝
        vector<vector<int>> f(n + 1, vector<int>(m));
        f[0][0] = (floor[0] == '1');
        for (int i = 1; i < m; ++i)
            f[0][i] = f[0][i - 1] + (floor[i] == '1');
        for (int i = 1; i <= n; ++i)
            // j < carpetLen * i 的 f[i][j] 均为 0
            for (int j = carpetLen * i; j < m; ++j)
                f[i][j] = min(f[i][j - 1] + (floor[j] == '1'), f[i - 1][j - carpetLen]);
        return f[n][m - 1];
    }
};

