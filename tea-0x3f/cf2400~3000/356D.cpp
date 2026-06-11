#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif
#include <format>
#include <concepts>
#include <ranges>

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

template<typename T>
void __print(const T&);

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
	apply([&]<typename... Args>(const Args &... args) {
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
	if (x) {
		cerr << "Some(";
		__print(*x);
		cerr << ')';
	}
	else cerr << "None";
}

void _print() { cerr << "]\n"; }

template<typename T, typename... V>
void _print(T&& t, V &&... v) {
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

inline constexpr int MAXN = 70005;
inline constexpr int INF = 0x3f3f3f3f;
inline constexpr ll LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int MOD_197 = 1'000'000'007;
inline constexpr int MOD_998 = 998'244'353;
inline constexpr int MAXB = 30;

inline constexpr int MAXV = 70005;
inline constexpr int K = 100;

bitset<MAXV> dp[MAXN / K + 5];
int w[MAXN];

void solve() {
	int n, s;
	cin >> n >> s;

	for (int i = 1; i <= n; ++i) cin >> w[i];

	vi ids(n);
	iota(ids.begin(), ids.end(), 1);
	ranges::sort(ids, [&](int i, int j) { return w[i] < w[j]; });

	if (n == 1) {
		if (s == w[1]) {
			cout << s << ' ' << 0 << '\n';
		}
		else cout << -1 << '\n';
		return;
	}

	vi path;
	path.push_back(n - 1); // the biggest one, it must be in the solution
	s -= w[ids[n - 1]];
	--n;

	if (s < 0) {
		cout << -1 << '\n';
		return;
	}

	if (s) {
		bitset<MAXV> cur;
		cur[0] = 1;
		dp[0] = cur;

		for (int i = 0; i < n; ++i) {
			if (i % K == 0) dp[i / K] = cur;
			cur = cur | (cur << w[ids[i]]);
		}

		if (!cur[s]) {
			cout << -1 << '\n';
			return;
		}

		int cur_s = s, cur_idx = n;

		while (cur_idx > 0) {
			int st = (cur_idx - 1) / K * K;
			int ed = cur_idx;

			vec<bitset<MAXV>> f(ed - st + 1);
			f[0] = dp[st / K];

			for (int i = 1; i <= ed - st; ++i) {
				f[i] = f[i - 1] | (f[i - 1] << w[ids[i + st - 1]]);
			}

			for (int i = ed - st; i >= 1; --i) {
				int idx = ids[i + st - 1];
				if (cur_s >= w[idx] && f[i - 1][cur_s - w[idx]]) {
					path.push_back(i + st - 1);
					cur_s -= w[idx];
				}
			}

			cur_idx = st;
		}
	}

	reverse(path.begin(), path.end());
	++n;

	int m = path.size();
	// (1..path[0]), (path[0] + 1 ... path[1]) ...
	vi arr(n + 1);
	vi ref(n + 1);
	for (int i = 0, j = 0; i < m; ++i) {
		arr[ids[j]] = w[ids[j]];
		for (int k = j + 1; k <= path[i]; ++k) {
			arr[ids[k]] = w[ids[k]] - w[ids[k - 1]];
			ref[ids[k]] = ids[k - 1];
		}
		j = path[i] + 1;
	}

	for (int i = 1; i <= n; ++i) {
		cout << arr[i] << ' ' << (ref[i] ? 1 : 0);
		if (ref[i]) cout << ' ' << ref[i];
		cout << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}