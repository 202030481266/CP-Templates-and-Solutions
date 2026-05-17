// Problem: C. Arpa’s overnight party and Mehrdad’s silent entering
// Contest: Codeforces - Codeforces Round 383 (Div. 1)
// URL: https://codeforces.com/problemset/problem/741/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

inline constexpr int  MAXN = 1000005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;


// 所有的点的入度为3，那么本质上一定可以出现解决的方法？
// 划分组，两个为一组就行了。然后开始遍历，可以证明遍历结束一次之后，经过的不同的点的总数是偶数，而且每一个组的颜色分布相同。
// 继续遍历剩下的组。因为每一个组都包含0-1，那么任意三个点不可能是相同的，因此符合条件

void solve() {
	int n;
	cin >> n;
	vp arr(n);
	vi ref(2 * n);
	for (auto& [u, v] : arr) {
		cin >> u >> v;
		--u;
		--v;
		ref[u] = v;
		ref[v] = u;
	}
	// [0,1] [2,3] ...
	vi c(2 * n);
	vi vis(2 * n);
	int cur = 0;
	for (int i = 0; i < n * 2; ++i) {
		if (vis[i]) continue;
		int x = i, go = 1;
		while (!vis[x]) {
			vis[x] = 1;
			c[x] = cur;
			cur ^= 1;
			if (go) { // go other group
				x = ref[x];
				go ^= 1;
			}
			else { // go same group
				x = x ^ 1;
				go ^= 1;
			}
		}
	}
	for (auto [u, v] : arr) {
		cout << c[u] + 1 << ' ' << c[v] + 1 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}