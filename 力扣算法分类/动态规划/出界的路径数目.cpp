// https://leetcode.cn/problems/out-of-boundary-paths/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    	swap(n, m);

    	vector dp(n, vector (m, vector<int>(maxMove + 1, -1)));
    	vector<int> dx{-1, 0, 1, 0};
    	vector<int> dy{0, 1, 0, -1};

    	auto f = [&](int x, int y) {
    		return (x >= 0) && (y >= 0) && (x < n) && (y < m);
    	};

    	function<int(int,int,int)> dfs = [&](int i, int j, int p) -> int {
    		if (!f(i, j)) return 1;
    		if (dp[i][j][p] != -1) return dp[i][j][p];
    		if (p == 0) {
    			return dp[i][j][0] = 0;
    		}

    		long long res = 0;
    		for (int d = 0; d < 4; ++d) {
    			int x = i + dx[d], y = j + dy[d];
    			res = (res + dfs(x, y, p - 1)) % mod;
    		}
    		return dp[i][j][p] = res;
    	};

    	return dfs(startRow, startColumn, maxMove);
    }
};