#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size(), m = isWater[0].size();
        vector<pii> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (isWater[i][j] == 1) {
                    q.push_back({i, j});
                }
            }
        }
        while (!q.empty()) {
            vector<pii> tmp;
            for (auto [x, y] : q) {
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && isWater[nx][ny] == 0) {
                        isWater[nx][ny] = isWater[x][y] + 1;
                        tmp.push_back({nx, ny});
                    }
                }
            }
            q = move(tmp);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                isWater[i][j]--;
            }
        }
        return isWater;
    }
};