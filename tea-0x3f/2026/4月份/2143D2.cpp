#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

#include <format>       // std::format
#include <concepts>     // concepts
#include <ranges>       // std::ranges

using namespace std;

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using ld = long double;

template<typename T, typename U = T>
using pr = pair<T, U>;

template<typename T>
using vec = vector<T>;

using pii = pr<int>;
using pll = pr<ll>;
using vi = vec<int>;
using vl = vec<ll>;
using vii = vec<vi>;
using vll = vec<vl>;
using vp = vec<pii>;
using vpp = vec<vp>;

template<typename T>
concept Printable = requires(T x) { cerr << x; };

template<typename T>
concept PairLike = requires(T x) { x.first; x.second; };

template<typename T>
concept Iterable = ranges::range<T> && !PairLike<T> && !is_convertible_v<T, string_view>;

template<typename T> void __print(const T&);

void __print(char x) { cerr << '\'' << x << '\''; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
void __print(const char* x) { cerr << '"' << x << '"'; }
void __print(const string& x) { cerr << '"' << x << '"'; }
void __print(string_view x) { cerr << '"' << x << '"'; }
template<Printable T>
	requires (!PairLike<T> && !Iterable<T>
&& !is_same_v<T, char>
&& !is_same_v<T, bool>
&& !is_same_v<T, string>
&& !is_same_v<T, string_view>
&& !is_convertible_v<T, const char*>)
void __print(const T& x) { cerr << x; }

template<PairLike T>
void __print(const T& x) {
	cerr << '{';
	__print(x.first);
	cerr << ", ";
	__print(x.second);
	cerr << '}';
}

template<typename... Ts>
void __print(const tuple<Ts...>& t) {
	cerr << '(';
	apply([&]<typename... Args>(const Args&... args) {
		size_t n = 0;
		((cerr << (n++ ? ", " : ""), __print(args)), ...);
	}, t);
	cerr << ')';
}

template<Iterable T>
void __print(const T& x) {
	cerr << '{';
	bool first = true;
	for (const auto& i : x) {
		if (!first) cerr << ", ";
		__print(i);
		first = false;
	}
	cerr << '}';
}

template<typename T>
void __print(const optional<T>& x) {
	if (x) { cerr << "Some("; __print(*x); cerr << ')'; }
	else     cerr << "None";
}

void _print() { cerr << "]\n"; }

template<typename T, typename... V>
void _print(T&& t, V&&... v) {
	__print(t);
	if constexpr (sizeof...(v) > 0) cerr << ", ";
	_print(forward<V>(v)...);
}

#ifndef ONLINE_JUDGE
#   define debug(...) \
        cerr << std::format("[{}:{}] [{}] = [", __FILE_NAME__, __LINE__, #__VA_ARGS__); \
        _print(__VA_ARGS__)
#else
#   define debug(...)
#endif

inline constexpr int  MAXN = 2003;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;


ll dp[MAXN][MAXN];
ll fenwick_row[MAXN][MAXN];
ll fenwick_col[MAXN][MAXN];
int n, arr[MAXN];


void add_row(int r, int c, ll val) {
	r++; c++;	
	for (; c <= n + 1; c += c & -c) {
		fenwick_row[r][c] = (fenwick_row[r][c] + val) % MOD;
	}
}

ll query_row(int r, int c) {
	if (c < 0) return 0;
	r++; c++;
	ll sum = 0;
	for (; c > 0; c -= c & -c) {
		sum = (sum + fenwick_row[r][c]) % MOD;
	}
	return sum;
}

void add_col(int c, int r, ll val) {
	c++; r++;
	for (; r <= n + 1; r += r & -r) {
		fenwick_col[c][r] = (fenwick_col[c][r] + val) % MOD;
	}
}

ll query_col(int c, int r) {
	if (r < 0) return 0;
	c++; r++;
	ll sum = 0;
	for (; r > 0; r -= r & -r) {
		sum = (sum + fenwick_col[c][r]) % MOD;
	}
	return sum;
}


void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];

	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= n + 1; ++j) {
			dp[i][j] = 0;
			fenwick_row[i][j] = 0;
			fenwick_col[i][j] = 0;
		}
	}

	dp[0][0] = 1;
	add_row(0, 0, 1);
	add_col(0, 0, 1);

	for (int k = 1; k <= n; ++k) {
		int v = arr[k];

		vector<pair<pair<int, int>, ll>> updates;

		for (int u = 0; u <= n; ++u) {
			if (v > u) {
				ll add_val = 0;
				if (u > 0) {
					// dp[u][v] += sum(dp[u][j]) for j in [u+1, v]
					add_val = query_row(u, v) - query_row(u, u);
				}
				else {
					// dp[0][v] += sum(dp[0][j]) for j in [0, v]
					add_val = query_row(0, v);
				}
				add_val = (add_val % MOD + MOD) % MOD;
				updates.push_back({ {u, v}, add_val });
			}
			else if (u > v) {
				// dp[v][u] += sum(dp[j][u]) for j in [0, v] 
				ll add_val = query_col(u, v);
				add_val = (add_val % MOD + MOD) % MOD;
				updates.push_back({ {v, u}, add_val });
			}
		}

		for (auto& p : updates) {
			int r = p.first.first;
			int c = p.first.second;
			ll delta = p.second;
			dp[r][c] = (dp[r][c] + delta) % MOD;
			add_row(r, c, delta);
			add_col(c, r, delta);
		}
	}
	
	ll ans = 0;
	for (int i = 0; i <= n; ++i) {
		ans = (ans + query_row(i, n)) % MOD;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t; 
	while (t--) solve();
	return 0;
}