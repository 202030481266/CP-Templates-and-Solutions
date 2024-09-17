#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int sx, sy; 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '*') {
                    sx = i;
                    sy = j;
                }
            }
        }
        queue<pii> q;
        q.push({sx, sy});
        vector<vector<int>> dis(n, vector<int>(m, INF));
        dis[sx][sy] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (grid[x][y] == '#') {
                return dis[x][y];
            }
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != 'X' && dis[nx][ny] == INF) {
                    dis[nx][ny] = dis[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return -1;
    }
};