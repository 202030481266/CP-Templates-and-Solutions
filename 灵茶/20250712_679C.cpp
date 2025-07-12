#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 503;

int belong[maxn][maxn], n, k;
int vis[maxn][maxn];
int around[maxn][maxn][4];
int cnt[maxn * maxn];
int cur[maxn * maxn];
char g[maxn][maxn];

static constexpr int dirs[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

void dfs(int x, int y, int b) {
	vis[x][y] = 1;
	belong[x][y] = b;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dirs[i][0], ny = y + dirs[i][1];
		if (nx < 1 || ny < 1 || nx > n || ny > n || vis[nx][ny] || g[nx][ny] == 'X') continue;
		dfs(nx, ny, b);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> g[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (!vis[i][j] && g[i][j] == '.') {
				dfs(i, j, (i - 1) * n + j);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (g[i][j] == '.') {
				++cnt[belong[i][j]];
				ans = max(ans, cnt[belong[i][j]]);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (g[i][j] == 'X') {
				for (int d = 0; d < 4; ++d) {
					int ni = i + dirs[d][0], nj = j + dirs[d][1];
					if (ni >= 1 && ni <= n && nj >= 1 && nj <= n && g[ni][nj] == '.') {
						around[i][j][d] = belong[ni][nj];
					}
				}
			}
		}
	}
	for (int i = 1, l, add = 0, sz = 0; i + k - 1 <= n; ++i) {
		l = 1;
		for (int j = 1; j <= n; ++j) {
			for (int r = i; r < i + k; ++r) {
				if (g[r][j] == 'X') {
					++add;
					for (int x = 0; x < 4; ++x) {
						++cur[around[r][j][x]];
						if (cur[around[r][j][x]] == 1) sz += cnt[around[r][j][x]];
					}
				}
			}
			if (j - l + 1 > k) {
				for (int r = i; r < i + k; ++r) {
					if (g[r][l] == 'X') {
						--add;
						for (int x = 0; x < 4; ++x) {
							--cur[around[r][l][x]];
							if (cur[around[r][l][x]] == 0) sz -= cnt[around[r][l][x]];
						}
					}
				}
				++l;
			}
			ans = max(ans, sz + add);
		}
		// clear cur array
		while (l <= n) {
			for (int r = i; r < i + k; ++r) {
				if (g[r][l] == 'X') {
					--add;
					for (int x = 0; x < 4; ++x) {
						--cur[around[r][l][x]];
						if (cur[around[r][l][x]] == 0) sz -= cnt[around[r][l][x]];
					}
				}
			}
			++l;
		}
		// assert(sz == 0);
		// assert(add == 0);
	}
	cout << ans << endl;
}