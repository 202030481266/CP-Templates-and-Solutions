#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using item = tuple<int, int, int, int>;
    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        //  距离 > 价格 > 行坐标 > 列坐标    
        int n = grid.size(), m = grid[0].size(), dis[n][m];
        memset(dis, 0x3f, sizeof(dis));
        dis[start[0]][start[1]] = 0;
        queue<pair<int, int>> q;
        q.emplace(start[0], start[1]);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + "2011"[i] - '1', ny = y + "1102"[i] - '1';
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] > 0) { // 有墙壁
                    if (dis[nx][ny] > dis[x][y] + 1) {
                        dis[nx][ny] = dis[x][y] + 1;
                        q.emplace(nx, ny);
                    }
                }
            }
        }
        priority_queue<item> pq;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] >= pricing[0] && grid[i][j] <= pricing[1] && dis[i][j] < 0x3f3f3f3f) {
                    // 要判断是否可达
                    pq.emplace(dis[i][j], grid[i][j], i, j);
                    if (pq.size() > k) {
                        pq.pop();
                    }
                }
            }
        }
        vector<vector<int>> ans;
        while (!pq.empty()) {
            auto [_, __, x, y] = pq.top();
            pq.pop();
            ans.push_back({x, y});
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
