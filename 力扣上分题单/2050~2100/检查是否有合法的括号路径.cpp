// https://leetcode.cn/problems/check-if-there-is-a-valid-parentheses-string-path/



class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
    	// starts from '(' ends with ')'
    	// anytime the number of left parenthesis >= right parenthesis

    	int n = grid.size(), m = grid[0].size();

		if ((m + n) % 2 == 0) return false;

    	if (grid[0][0] != '(' || grid[n - 1][m - 1] != ')') return false;
    	vector dp(n, vector(m, vector<int>(n + m + 1, 0)));

    	queue<tuple<int, int, int>> q;
    	q.emplace(0, 0, 1);
    	dp[0][0][1] = 1;

    	while (!q.empty()) {
    		auto [x, y, z] = q.front();
    		q.pop();

    		printf("%d %d %d\n", x, y, z);

			if (x == n - 1 && y == m - 1 && z == 0) return true;

    		// down
    		if (x + 1 < n) {
    			if (grid[x + 1][y] == '(') {
    				if (dp[x + 1][y][z + 1] == 0) {
	    				q.emplace(x + 1, y, z + 1);
	    				dp[x + 1][y][z + 1] = 1;
	    			}
    			}
    			else if (z > 0) {
    				if (dp[x + 1][y][z - 1] == 0) {
	    				q.emplace(x + 1, y, z - 1);
	    				dp[x + 1][y][z - 1] = 1;
	    			}
	    		}
    		}
    		// right
    		if (y + 1 < m) {
    			if (grid[x][y + 1] == '(') {
    				if (dp[x][y + 1][z + 1] == 0) {
	    				q.emplace(x, y + 1, z + 1);
	    				dp[x][y + 1][z + 1] = 1;
	    			}
	    		}
    			else if (z > 0) {
    				if (dp[x][y + 1][z - 1] == 0) {
	    				q.emplace(x, y + 1, z - 1);
	    				dp[x][y + 1][z - 1] = 1;
	    			}
	    		}
    		}
    	}
    	return false;
    }
};