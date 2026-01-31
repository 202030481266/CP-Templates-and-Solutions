#include <bits/stdc++.h>
using namespace std;

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 1001;
static int dis[maxn][maxn];

static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<pii>> pos(26);
        auto isAlpha = [&](int x, int y) -> bool
            {
                return matrix[x][y] != '#' && matrix[x][y] != '.';
            };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dis[i][j] = 0x3f3f3f3f;
                if (isAlpha(i, j))
                {
                    pos[matrix[i][j] - 'A'].emplace_back(i, j);
                }
            }
        }
        queue<pii> q;
        if (isAlpha(0, 0))
        {
	        for (auto [x, y] : pos[matrix[0][0] - 'A'])
	        {
                dis[x][y] = 0;
                q.emplace(x, y);
	        }
        }
        else
        {
            dis[0][0] = 0;
            q.emplace(0, 0);
        }
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] != '#')
                {
	                if (dis[nx][ny] > dis[x][y] + 1)
	                {
                        if (isAlpha(nx, ny))
                        {
	                        for (auto [xx, yy] : pos[matrix[nx][ny] - 'A'])
	                        {
                                dis[xx][yy] = dis[x][y] + 1;
                                q.emplace(xx, yy);
	                        }
                        }
                        else
                        {
                            dis[nx][ny] = dis[x][y] + 1;
                            q.emplace(nx, ny);
                        }
	                }
                }
            }
        }
        return dis[n - 1][m - 1] == 0x3f3f3f3f ? -1 : dis[n - 1][m - 1];
    }
};