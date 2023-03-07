// https://leetcode.cn/problems/knight-probability-in-chessboard/



class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
    	vector f(n, vector (n, vector<double>(k + 1, 0)));
    	vector g(n, vector (n, vector<bool>(k + 1, false)));

    	vector<int> dx{-1, -2, -2, -1, 1, 2, 2, 1};
    	vector<int> dy{-2, -1, 1, 2, 2, 1, -1, -2};

    	auto check = [&](int x, int y) {
    		return (x < 0) || (y < 0) || (x >= n) || (y >= n);
    	};

    	function<double(int,int,int)> dfs = [&](int x, int y, int z) -> double {
    		if (check(x, y)) return 0.0;
    		if (z == 0) return 1.0 / pow(8, k - z);
    		if (g[x][y][z]) return f[x][y][z];

    		g[x][y][z] = true;

    		double sum = 0;
    		for (int i = 0; i < 8; ++i) {
    			double nxt = dfs(x + dx[i], y + dy[i], z - 1);
    			sum += nxt;
    		}
    		return f[x][y][z] = sum;
    	};
    	return dfs(row, column, k);
    }
};