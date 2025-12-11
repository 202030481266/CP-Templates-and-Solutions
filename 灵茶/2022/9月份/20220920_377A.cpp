// Problem: A. Maze
// Contest: Codeforces - Codeforces Round 222 (Div. 1)
// URL: https://codeforces.com/problemset/problem/377/A
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, m, k, vis[503][503];
char g[503][503];

static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> g[i][j];
    }
    auto dfs = [&](auto&& self, int x, int y) -> void {
        if (k == 0) return;
        vis[x][y] = 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0], ny = y + dirs[i][1];
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny] && g[nx][ny] == '.') self(self, nx, ny);
        }
        if (k > 0) {
            --k;
            g[x][y] = 'X';
        }
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!vis[i][j] && g[i][j] == '.' && k > 0) dfs(dfs, i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << g[i][j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}