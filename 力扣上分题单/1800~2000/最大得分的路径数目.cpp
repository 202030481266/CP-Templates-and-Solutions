// https://leetcode.cn/problems/number-of-paths-with-max-score/
// 经典的最短路计数问题



class Solution {
public:
	static constexpr int mod = 1000000007;
    vector<int> pathsWithMaxScore(vector<string>& board) {
    	int n = board.size();

    	auto f = [&](int x, int y) -> bool {
    		return (x >= 0 && y >= 0 && x < n && y < n) && (board[x][y] != 'X');
    	};
    	auto id = [&](int x, int y) -> int {
    		return x * n + y;
    	};

    	vector dp(n + 1, vector<int>(n + 1));
    	vector dis(n + 1, vector<int>(n + 1));
    	vector vis(n + 1, vector<bool>(n + 1));
    	vector<int> dx{1, 1, 0};
    	vector<int> dy{1, 0, 1};

    	dis[0][0] = 0;
    	dp[0][0] = 1;
    	vis[0][0] = true;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < n; ++j) {
    			if (board[i][j] == 'X') continue;
    			if (!vis[i][j]) continue;
    			for (int k = 0; k < 3; ++k) {
    				int x = i + dx[k], y = j + dy[k];
    				if (f(x, y)) {
    					char ch = board[x][y];
    					int cost = (ch == 'S' ? 0 : 0 - (ch - '0'));
    					vis[x][y] = true;
    					if (dis[x][y] > dis[i][j] + cost) {
    						dis[x][y] = dis[i][j] + cost;
    						dp[x][y] = dp[i][j];
    					} else if (dis[x][y] == dis[i][j] + cost) {
    						dp[x][y] = (dp[x][y] + dp[i][j]) % mod;
    					}
    				}
    			}
    		}
    	}
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < n; ++j) cout << dis[i][j] << ' ';
        //     cout << endl;
        // }
    	if (!vis[n - 1][n - 1]) return {0, 0};
    	return {0 - dis[n - 1][n - 1], dp[n - 1][n - 1]};
    }
};