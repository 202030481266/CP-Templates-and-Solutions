#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

const int INF = 2147483647;

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int n = rooms.size(), m = rooms[0].size();
        vector<pii> q;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rooms[i][j] == 0) {
                    q.push_back({i, j});
                }
            }
        }
        for(int d = 1; !q.empty(); ++d) {
            vector<pii> tmp;
            for (auto [i, j] : q) {
                for (auto [dx, dy] : vector<pii>{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}) {
                    int x = i + dx, y = j + dy;
                    if (x >= 0 && x < n && y >= 0 && y < m && rooms[x][y] == INF) {
                        rooms[x][y] = d;
                        tmp.push_back({x, y});
                    }
                }
            }
            q = move(tmp);
        }
        return;
    }
};