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

static constexpr int MAXN = 2e5 + 7;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
struct ST {
	int N;
	vector<vector<T>> vec;

	ST() {}

	ST(int n) : N(n) {
		vec.assign(N + 1, vector<T>(30));
		for (int i = 1; i <= N; i++) {
			cin >> vec[i][0];
		}
	}

	ST(const vector<T>& a) {
		N = a.size() - 1;
		vec.assign(N + 1, vector<T>(30));
		for (int i = 1; i <= N; i++) {
			vec[i][0] = a[i];
		}
	}

	void ST_work() {
		int t = log2(N) + 1;
		for (int i = 1; i < t; i++) {
			for (int j = 1; j + (1 << i) - 1 <= N; j++) {
				vec[j][i] = min(vec[j][i - 1], vec[j + (1 << (i - 1))][i - 1]);
			}
		}
	}

	T query(int l, int r) {
		int k = __lg(r - l + 1);
		return min(vec[l][k], vec[r - (1 << k) + 1][k]);
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	vii arr(1 + n, vi(1 + m));
	char ch;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> ch;
			arr[i][j] = ch - 'a';
		}
	}
	vii dp(2, vi(n + 1));
	int pre = 0, cur = 1;
	ll ans = 0;
	for (int col = 1; col <= m; ++col) {
		for (int row = 1; row <= n; ++row) {
			dp[cur][row] = 1;
			if (col > 1 && arr[row][col - 1] == arr[row][col]) dp[cur][row] += dp[pre][row];
		}
		ST<int> table(dp[cur]);
		table.ST_work();
		vector<pii> pos;
		int p = 1;
		while (p <= n) {
			int i = p + 1;
			while (i <= n && arr[i][col] == arr[p][col]) ++i;
			pos.emplace_back(p, i - p);
			p = i;
		}
		for (int i = 1; i < (int)pos.size() - 1; ++i) {
			int last = pos[i - 1].second;
			int nxt = pos[i + 1].second;
			if (last >= pos[i].second && nxt >= pos[i].second) {
				last = pos[i].first - pos[i].second;
				nxt = pos[i + 1].first + pos[i].second - 1;
				ans += table.query(last, nxt);
			}
		}
		swap(pre, cur);
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}

