#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int n = grid.size(), m = grid[0].size();

    	vector<int> dx{-1, 1, 0, 0};
    	vector<int> dy{0, 0, 1, -1};
    	vector dis(n, vector<int>(m, 0x3f3f3f3f));
    	dis[0][0] = grid[0][0];

    	deque<pair<int, int>> q;
		q.emplace_front(0, 0);
    	while (!q.empty()) {
    		auto [x, y] = q.front();
    		q.pop_front();
    		for (int k = 0; k < 4; ++k) {
    			int nx = x + dx[k], ny = y + dy[k];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    			if (grid[nx][ny]) {
    				// 障碍物
    				if (dis[nx][ny] > dis[x][y] + 1) {
    					dis[nx][ny] = dis[x][y] + 1;
    					q.emplace_back(nx, ny);
    				}
    			}
    			else {
    				if (dis[nx][ny] > dis[x][y]) {
    					dis[nx][ny] = dis[x][y];
    					q.emplace_front(nx, ny);
    				}
    			}
    		}
    	}
        return dis[n-1][m-1] < health;
    }
};