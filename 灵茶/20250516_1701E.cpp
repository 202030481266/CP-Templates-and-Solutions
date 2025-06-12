// https://codeforces.com/problemset/problem/1701/E
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;

char s[5003], t[5003];
int n, m;
int dp[5003][5003], f[5003][5003];
int last[5003][26], fm[5003], g[5003], pos[5003];

int dfs(int l, int r) {
	if (r == 0) return l;
	if (l == 0) return inf;
	if (dp[l][r] != -1) return dp[l][r];
	int& res = dp[l][r];
	res = inf;
	if (s[l] != t[r]) {
		// must delete
		res = min(res, dfs(last[l][t[r] - 'a'], r) + l - last[l][t[r] - 'a']);
	}
	else {
		if (f[l][r] == l) {
			res = 0;
			return res;
		}
		res = min(res, dfs(l - 1, r - 1) + 1);
		res = min(res, l - f[l][r] + l - r + 1);
		if (fm[r] < l) {
			// delete
			res = min(res, dfs(last[l][t[r]-'a'], r) + l - last[l][t[r]-'a']);
		}
	}
	return res;
}


void solve() {
	cin >> n >> m;
	memset(pos, 0, sizeof(pos));
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 26; ++j) last[i][j] = 0;
		fm[i] = 0;
		g[i] = 0;
	}
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int i = 1; i <= m; ++i) cin >> t[i];
	int p = 1;
	for (int i = 1; i <= n && p <= m; ++i) {
		if (s[i] == t[p]) {
			fm[p] = i;
			g[i] = g[i - 1] + 1;
			++p;
		}
	}
	if (p <= m) {
		std::cout << -1 << '\n';
		return;
	}
	for (int i = 1; i <= n; ++i) {
		int c = s[i] - 'a';
		for (int j = 0; j < 26; ++j) {
			last[i][j] = pos[j];
		}
		pos[c] = i;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = -1;
			f[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f[i][j] = (s[i] == t[j] ? f[i - 1][j - 1] + 1 : 0);
		}
	}
	std::cout << dfs(n, m) << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}