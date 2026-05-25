// Problem: E. Greedy Change
// Contest: Codeforces - Codeforces Beta Round 10
// URL: https://codeforces.com/problemset/problem/10/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

inline constexpr int  MAXN = 300005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;


void solve() {
	int n;
	cin >> n;
	vi arr(n);
	for (int& v : arr) cin >> v;

	if (n <= 2) {
		cout << -1 << '\n';
		return;
	}

	auto greedy = [&](int st, int val) -> int {
		int res = 0;
		for (int i = st; i < n; ++i) {
			int v = arr[i];
			int d = val / v;
			res += d;
			val -= d * v;
		}
		return res;
	};

	int ans = INF;
	for (int i = n - 3; i >= 0; --i) {
		int T = arr[i] / arr[i + 1];
		int start = T * arr[i + 1];
		int r = i == 0 ? INF : arr[i - 1];
		for (int j = i + 1; j < n; ++j) {
			int val = (arr[i] - start + arr[j] - 1) / arr[j];
			val = start + val * arr[j];
			if (val < r) {
				int cur_use = greedy(i, val);
				int pre_use = greedy(i + 1, val);
				if (cur_use > pre_use) {
					ans = min(ans, val);
				}
			}
		}
	}

	for (int i = n - 1; i > 0; --i) {
		for (int j = i - 1; j >= 0; --j) {
			int t = (arr[j] + arr[i] - 1) / arr[i];
			int val = t * arr[i];
			if (greedy(0, val) > t) {
				ans = min(ans, val);
				break;
			}
		}
	}

	cout << (ans == INF ? -1 : ans) << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) {
		solve();
	}
	return 0;
}