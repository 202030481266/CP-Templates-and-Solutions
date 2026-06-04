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
inline constexpr int  MOD_197 = 1'000'000'007;
inline constexpr int  MOD_998 = 998'244'353;
inline constexpr int  MAXB = 30;


void solve() {
	int n, m, L;
	cin >> n >> m >> L;
	// s[i] % m == 0, s[i + 1] % m == 0
	// a[i] % m == a[i + L] % m
	vi arr(n);
	for (int& v : arr) cin >> v;
	int ans = 0;
	vi f(m);
	vii dp(2, vi(m, INF));
	int pre = 0, cur = 1;
	dp[pre][0] = 0;
	for (int x = 0; x < L; ++x) {
		vi b;
		for (int j = x; j < n; j += L) {
			b.push_back(arr[j] % m);
		}
		ranges::sort(b);
		int N = b.size();
		vi pres(b.size());
		vi suf(b.size());
		pres[0] = b[0];
		for (int i = 1; i < N; ++i) pres[i] = pres[i - 1] + b[i];
		suf[N - 1] = m - b[N - 1];
		for (int i = N - 2; i >= 0; --i) suf[i] = suf[i + 1] + m - b[i];
		int p = 0;
		for (int i = 0; i < m; ++i) {
			while (p < N && b[p] <= i) ++p;
			f[i] = i * N;
			if (p > 0) f[i] -= pres[p - 1];
			if (p < N) f[i] += suf[p];
		}
		for (int i = 0; i < m; ++i) dp[cur][i] = INF;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < m; ++j) {
				int y = (i + j) % m;
				dp[cur][y] = min(dp[cur][y], dp[pre][i] + f[j]);
			}
		}
		swap(pre, cur);
	}

	cout << dp[pre][0] << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}