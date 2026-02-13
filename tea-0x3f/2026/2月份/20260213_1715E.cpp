#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

ll dp[21][MAXN];
int head[MAXN], to[MAXN << 1], weight[MAXN << 1], nxt[MAXN << 1], tot = 0;
int n, m, k;

void addEdge(int u, int v, int w) {
	to[++tot] = v;
	nxt[tot] = head[u];
	weight[tot] = w;
	head[u] = tot;
}

using node = pair<ll, int>;

void dijkstra(ll* dis) {
	priority_queue<node, vector<node>, greater<node>> q;
	for (int i = 1; i <= n; ++i) {
		q.emplace(dis[i], i);
	}
	while (!q.empty()) {
		auto [d, u] = q.top();
		q.pop();
		if (dis[u] != d) continue;
		for (int i = head[u]; i; i = nxt[i]) {
			int v = to[i], w = weight[i];
			if (dis[v] > d + w) {
				dis[v] = d + w;
				q.emplace(dis[v], v);
			}
		}
	}
}

int que[MAXN], ql, qr;

void slop_optimize(int layer) {
	ll* pre = dp[layer], * cur = dp[layer + 1];
	// use dp[layer][*] update dp[layer + 1][*]
	// cur[x] = min(pre[y] + (x - y) ^ 2)
	// cur[x] = pre[y] + x^2 + y^2 - 2xy
	// cur[x] - x^2 + 2xy = pre[y] + y^2
	ql = qr = 0;
	for (int i = 1; i <= n; ++i) {
		while (qr - ql >= 2) {
			ll p1 = que[qr - 2], p2 = que[qr - 1], p3 = i;
			ll x21 = p2 - p1, y21 = pre[p2] + p2 * p2 - pre[p1] - p1 * p1;
			ll x32 = p3 - p2, y32 = pre[p3] + p3 * p3 - pre[p2] - p2 * p2;
			if ((__int128)x21 * y32 <= (__int128)x32 * y21) --qr;
			else break;
		}
	}
	for (int i = 1; i <= n; ++i) {
		ll cur_slope = 2 * i;
		while (qr - ql >= 2) {
			ll p1 = que[ql], p2 = que[ql + 1];
			ll dy = pre[p2] + p2 * p2 - pre[p1] - p1 * p1;
			ll dx = p2 - p1;
			if ((__int128)dy <= (__int128)dx * cur_slope) ++ql;
			else break;
		}
		cur[i] = pre[que[ql]] + 1ll * (i - que[ql]) * (i - que[ql]);
	}
}

void solve() {
	cin >> n >> m >> k;
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0, u, v, w; i < m; ++i) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	dp[0][1] = 0;
	for (int t = 0; t <= k; ++t) {
		dijkstra(dp[0]);
		if (t < k) slop_optimize(t);
	}
	for (int i = 1; i <= n; ++i) {
		ll d = dp[i][0];
		for (int j = 1; j <= k; ++j) d = min(d, dp[i][j]);
		cout << d << ' ';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;
}