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

inline constexpr int  MAXN = 100'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;


void solve() {
	int n, m;
	cin >> n >> m;

	vi arr(n);
	for (int& v : arr) cin >> v;

	vp a(m);
	ll total_capacity = 0;
	for (auto& [p, c] : a) {
		cin >> p >> c;
		total_capacity += c;
	}

	if (total_capacity < n) {
		cout << -1 << "\n";
		return;
	}

	ranges::sort(arr);
	ranges::sort(a);

	vll dp(m + 1, vl(n + 1, LL_INF));
	dp[0][0] = 0;

	for (int i = 1; i <= m; ++i) {
		ll p = a[i - 1].first;
		ll c = a[i - 1].second;

		vl cost(n + 1, 0);
		for (int j = 1; j <= n; ++j) {
			cost[j] = cost[j - 1] + abs(arr[j - 1] - p);
		}

		deque<int> dq;

		for (int j = 0; j <= n; ++j) {
			while (!dq.empty() && dq.front() < j - c) {
				dq.pop_front();
			}
			ll cur_val = (dp[i - 1][j] == LL_INF) ? LL_INF : dp[i - 1][j] - cost[j];
			while (!dq.empty()) {
				int back_idx = dq.back();
				ll back_val = (dp[i - 1][back_idx] == LL_INF) ? LL_INF : dp[i - 1][back_idx] - cost[back_idx];

				if (cur_val <= back_val) {
					dq.pop_back();
				}
				else {
					break;
				}
			}
			dq.push_back(j);
			int best_k = dq.front();
			if (dp[i - 1][best_k] != LL_INF) {
				dp[i][j] = dp[i - 1][best_k] - cost[best_k] + cost[j];
			}
		}
	}

	cout << dp[m][n] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}