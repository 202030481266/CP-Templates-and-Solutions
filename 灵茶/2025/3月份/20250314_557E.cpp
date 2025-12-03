#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5003;
static constexpr int maxm = maxn * (maxn + 1) / 2;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;

char s[maxn];
bool dp[maxn][maxn];
int ch[maxm][2], val[maxm], sum[maxm];
int n, tot, k;

void insert() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int len = 1; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			if (len == 1) dp[i][i] = 1;
			else {
				if (i + 2 <= j - 2) dp[i][j] = (s[i] == s[j]) && dp[i + 2][j - 2];
				else dp[i][j] = s[i] == s[j];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int u = 0;
		for (int j = i, v; j <= n; ++j) {
			v = s[j] - 'a';
			if (!ch[u][v]) ch[u][v] = ++tot;
			u = ch[u][v];
			if (dp[i][j]) ++val[u];
		}
	}
}

void dfs(int u) {
	if (!u) return;
	dfs(ch[u][0]);
	dfs(ch[u][1]);
	sum[u] = val[u] + sum[ch[u][0]] + sum[ch[u][1]];
}

int main() {
	insert();
	dfs(ch[0][0]);
	dfs(ch[0][1]);
	scanf("%d", &k);
	string ans;
	int cur = 0;
	while (true) {
		if (val[cur] >= k) { // end in this position
			cout << ans << endl;
			break;
		}
		k -= val[cur];
		if (k <= sum[ch[cur][0]]) {
			cur = ch[cur][0];
			ans.push_back('a');
		}
		else {
			k -= sum[ch[cur][0]];
			cur = ch[cur][1];
			ans.push_back('b');
		}
	}
}