#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5003;
static constexpr int maxm = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

int head[maxn << 2], to[maxm], nxt[maxm], ecnt = 0;
array<int, 2> qs[maxn];

void addEdge(int u, int qid) {
	to[++ecnt] = qid;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
}

vector<vector<int>> last;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void update(int rt, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		addEdge(rt, val);
		return;
	}
	if (R <= mid) update(lson, L, R, val);
	else if (L > mid) update(rson, L, R, val);
	else {
		update(lson, L, mid, val);
		update(rson, mid + 1, R, val);
	}
}

int dp[15][maxn], K;
int ans[maxn];

void dfs(int rt, int l, int r, int d) {
	for (int i = 0; i <= K; ++i) dp[d][i] = dp[d - 1][i];
	for (int i = head[rt]; i; i = nxt[i]) {
		for (int j = K; j >= to[i]; --j) dp[d][j] = (dp[d][j] + dp[d][j - to[i]]) % mod;
	}
	if (l == r) {
		ans[l] = dp[d][K];
	}
	else {
		dfs(lson, d + 1);
		dfs(rson, d + 1);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n >> K;
	last.resize(K + 1);
	for (int i = 1; i <= n; ++i) {
		char op;
		cin >> op;
		if (op == '+') qs[i][0] = 1;
		else qs[i][0] = -1;
		cin >> qs[i][1];
	}
	for (int i = 1; i <= n; ++i) {
		if (qs[i][1] > K) continue;
		if (qs[i][0] == 1) {
			last[qs[i][1]].push_back(i);
		}
		else {
			update(1, 1, n, last[qs[i][1]].back(), i - 1, qs[i][1]);
			last[qs[i][1]].pop_back();
		}
	}
	for (int i = 1; i <= K; ++i) {
		for (int v : last[i]) {
			update(1, 1, n, v, n, i);
		}
	}
	dp[0][0] = 1;
	dfs(1, 1, n, 1);
	for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
}