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

// 大坑，体力可以为浮点数

void solve() {
	int n;
	cin >> n;

	vl arr(n);
	vec<char> land(n);
	for (ll& v : arr) cin >> v;
	for (char& v : land) cin >> v;

	int N = 0;
	for (int i = 1; i < n; ++i) {
		if (land[i] == land[N]) {
			arr[N] += arr[i];
		}
		else {
			++N;
			arr[N] = arr[i];
			land[N] = land[i];
		}
	}

	arr.resize(N + 1);
	land.resize(N + 1);

	ll ans = 0;
	vi st;
	for (int i = 0; i <= N; ++i) {
		if (land[i] == 'W') {
			st.push_back(i);
		}
		else if (land[i] == 'L') {
			while (arr[i] && !st.empty()) {
				ll x = min(arr[st.back()], arr[i]);
				ans += 4 * x;
				arr[st.back()] -= x;
				arr[i] -= x;
				if (arr[st.back()] == 0) st.pop_back();
			}
		}
	}

	int flag = 0;
	ll gs = 0;
	ll ws = 0;
	for (int i = 0; i <= N; ++i) {
		if (land[i] == 'W') flag = 1;
		if (arr[i] == 0) continue;
		if (land[i] == 'W') ws += arr[i];
		else if (land[i] == 'G') {
			// it's impossible appear as "WGL"
			// always "GLGLGLWGWGWG"
			ll x = min(ws, arr[i]);
			ans += 4 * x;
			ws -= x;
			arr[i] -= x;
			gs += arr[i];
		}
		else {
			ll x = min(gs, arr[i]);
			ans += 6 * x;
			gs -= x;
			arr[i] -= x;
			if (arr[i]) {
				if (flag) ans += 4 * arr[i];
				else ans += 6 * arr[i];
			}
		}
	}

	ans += 3 * gs + 2 * ws;
	
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}