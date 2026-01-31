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
const int maxn = 50;

// 马的八个移动方向
const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};


void minMoves(vector<vector<int>>& dis, int kx, int ky) { // 预处理其中的
    vpii q;
    q.push_back({kx, ky});
    dis[kx][ky] = 0;
    while (!q.empty()) {
        vpii tmp;
        for (auto [x, y] : q) {
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < maxn && ny >= 0 && ny < maxn && dis[nx][ny] == -1) {
                    // not search
                    dis[nx][ny] = dis[x][y] + 1;
                    tmp.push_back({nx, ny});
                }
            }
        }
        q = move(tmp);
    }
}

class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size(), dp[1<<n][n][2];
        vector f(n+1, vector<vector<int>>(maxn, vector<int>(maxn,-1)));
        for (int i = 0; i < n; ++i) {
            minMoves(f[i], positions[i][0], positions[i][1]);
        }
        minMoves(f[n], kx, ky);

        // 不就是记忆化搜索？
        // O (n * 2 ^ n * n * 2) = 7e6
        memset(dp, -1, sizeof(dp));
        function<int(int,int,int)> dfs = [&](int status, int ed, int alice) -> int {
            if (status == 0) return 0;
            int& res = dp[status][ed][alice];
            if (res != -1) return res;
            if (alice) {
                // alice turn
                res = 0;
                for (int i = 0; i < n; ++i) {
                    if ((status >> i) & 1) {
                        res = max(res, dfs(status ^ (1<<i), i, 0) + f[ed][positions[i][0]][positions[i][1]]);
                    }
                }
            }
            else {
                // bob turn
                res = INF;
                for (int i = 0; i < n; ++i) {
                    if ((status >> i) & 1) {
                        res = min(res, dfs(status ^ (1<<i), i, 1) + f[ed][positions[i][0]][positions[i][1]]);
                    }
                }
            }
            return res;
        };
        int ans = 0, N = (1<<n)-1;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dfs(N ^ (1<<i), i, 0) + f[n][positions[i][0]][positions[i][1]]);
        }
        return ans;
    }
};