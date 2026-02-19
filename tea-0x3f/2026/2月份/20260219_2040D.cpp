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

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

vi prime(MAXN << 1, 1);

void get_primes(int n) {
	if (n == 1) return;
	prime[0] = prime[1] = 0;
	for (int i = 2; i * i <= n; i++)
		if (prime[i])
			for (int j = i * i; j <= n; j += i)
				prime[j] = 0;
}

void solve() {
	int n;
	cin >> n;
	vii g(n + 1);
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vi ans(n + 1);
	vi vis(n * 2 + 1);
	int cnt = 1;
	auto dfs = [&](auto&& self, int u, int fa) -> void {
		if (cnt == 1) ans[u] = 1;
		else {
			int p = ans[fa] & 1 ? ans[fa] + 1 : ans[fa] - 1;
			if (!vis[p]) ans[u] = p;
			else {
				if (!prime[cnt - ans[fa]]) ans[u] = cnt;
				else ans[u] = cnt + 1;
			}
		}
		vis[ans[u]] = 1;
		cnt += 2;
		for (int v : g[u]) {
			if (v != fa) self(self, v, u);
		}
	};
	dfs(dfs, 1, 0);
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	get_primes(400000);
	while (t--) solve();
	return 0;
}