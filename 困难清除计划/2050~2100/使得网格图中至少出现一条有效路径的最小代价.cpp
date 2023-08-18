// https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/



class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
    	// points means 4 types
    	int n = grid.size(), m = grid[0].size();

    	vector dis(n, vector(m, vector<int>(5, 0x3f3f3f3f)));
    	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;

    	for (int i = 1; i <= 4; ++i) {
    		if (grid[0][0] == i) q.emplace(0, 0, i), dis[0][0][i] = 0;
    		else q.emplace(1, 0, i), dis[0][0][i] = 1;
    	}
    	while (!q.empty()) {
    		auto [d, u, type] = q.top();
    		q.pop();
    		int x = u / m, y = u % m;
    		if (dis[x][y][type] != d) continue;

    		if (type == 1) {
    			// turn to right
    			if (y + 1 < m) {
    				for (int i = 1; i <= 4; ++i) {
    					if (grid[x][y + 1] == i) {
    						if (dis[x][y + 1][i] > d) {
    							dis[x][y + 1][i] = d;
    							q.emplace(dis[x][y + 1][i], x * m + y + 1, i);
    						}
    					}
    					else {
    						if (dis[x][y + 1][i] > d + 1) {
    							dis[x][y + 1][i] = d + 1;
    							q.emplace(dis[x][y + 1][i], x * m + y + 1, i);
    						}
    					}
    				}
    			} 
    		}
    		else if (type == 2) {
    			// turn to left
    			if (y - 1 >= 0) {
    				for (int i = 1; i <= 4; ++i) {
    					if (grid[x][y - 1] == i) {
    						if (dis[x][y - 1][i] > d) {
    							dis[x][y - 1][i] = d;
    							q.emplace(dis[x][y - 1][i], x * m + y - 1, i);
    						}
    					}
    					else {
    						if (dis[x][y - 1][i] > d + 1) {
    							dis[x][y - 1][i] = d + 1;
    							q.emplace(dis[x][y - 1][i], x * m + y - 1, i);
    						}
    					}
    				}
    			}
    		}
    		else if (type == 3) {
    			// turn to down
    			if (x + 1 < n) {
    				for (int i = 1; i <= 4; ++i) {
    					if (grid[x + 1][y] == i) {
    						if (dis[x + 1][y][i] > d) {
    							dis[x + 1][y][i] = d;
    							q.emplace(dis[x + 1][y][i], (x + 1) * m + y, i);
    						}
    					}
    					else {
    						if (dis[x + 1][y][i] > d + 1) {
    							dis[x + 1][y][i] = d + 1;
    							q.emplace(dis[x + 1][y][i], (x + 1) * m + y, i);
    						}
    					}
    				}
    			}
    		}
    		else {
    			// turn to up
    			if (x - 1 >= 0) {
    				for (int i = 1; i <= 4; ++i) {
    					if (grid[x - 1][y] == i) {
    						if (dis[x - 1][y][i] > d) {
    							dis[x - 1][y][i] = d;
    							q.emplace(dis[x - 1][y][i], (x - 1) * m + y, i);
    						}
    					}
    					else {
    						if (dis[x - 1][y][i] > d + 1) {
    							dis[x - 1][y][i] = d + 1;
    							q.emplace(dis[x - 1][y][i], (x - 1) * m + y, i);
    						}
    					}
    				}
    			}
    		}
    	}
    	return *min_element(dis[n - 1][m - 1].begin(), dis[n - 1][m - 1].end());
    }
};