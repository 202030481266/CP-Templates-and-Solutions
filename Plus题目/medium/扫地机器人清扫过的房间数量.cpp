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

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

class Solution {
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        int n = room.size(), m = room[0].size(), vis[n][m][4];
        memset(vis, 0, sizeof(vis));
        vis[0][0][0] = 1;
        int x = 0, y = 0, d = 0;
        while (true) {
            int nx = x + directions[d][0], ny = y + directions[d][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && room[nx][ny] == 0) {
                x = nx;
                y = ny;
                if (vis[x][y][d]) break;
                vis[x][y][d] = 1;
            } else {
                d = (d + 1) % 4;
                if (vis[x][y][d]) break;
                vis[x][y][d] = 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j][0] || vis[i][j][1] || vis[i][j][2] || vis[i][j][3]) ++ans;
            }
        }
        return ans;
    }
};
