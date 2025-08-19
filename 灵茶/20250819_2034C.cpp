#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 1003;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;
static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

char s[maxn][maxn];
int n, m, vis[maxn][maxn], cnt;

bool dfs(int x, int y) {
	if (x <= 0 || y <= 0 || x > n || y > m) return false; // 走出去了
	if (vis[x][y]) {
		if (vis[x][y] == 1 || vis[x][y] == 2) { // 遇到了环或者之前搜索到的走不通的
			vis[x][y] = 2;
			return true;
		}
		else {
			vis[x][y] = 3; // 走的通
			return false;
		}
	}
	vis[x][y] = 1;
	++cnt;
	bool res = false;
	if (s[x][y] == '?') {
		if (cnt > 1) res = true; // 可以构造死循环，因为?之前有人来
		else {
			for (int i = 0; i < 4; ++i) {
				if (dfs(x + dirs[i][0], y + dirs[i][1])) {
					res = true;
					break;
				}
			}
		}
	}
	else if (s[x][y] == 'L') res = dfs(x, y - 1);
	else if (s[x][y] == 'R') res = dfs(x, y + 1);
	else if (s[x][y] == 'U') res = dfs(x - 1, y);
	else res = dfs(x + 1, y);
	if (res) vis[x][y] = 2;
	else vis[x][y] = 3;
	return res;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> s[i][j];
			vis[i][j] = 0;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (!vis[i][j]) {
				cnt = 0;
				dfs(i, j);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (vis[i][j] == 2) ++ans;
		}
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}