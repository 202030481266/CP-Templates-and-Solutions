// Problem: E. The same permutation
// Contest: Codeforces - Codeforces Round 411 (Div. 1)
// URL: https://codeforces.com/problemset/problem/804/E
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
inline constexpr int  MOD_197 = 1'000'000'007;
inline constexpr int  MOD_998 = 998'244'353;
inline constexpr int  MAXB = 30;


void solve() {
	int n;
	cin >> n;
	vii vis(n + 1, vi(n + 1));
	vi arr(n + 1);
	vi pos(n + 1);
	vi cnt(n + 1);
	int tot = n * (n - 1) / 2;
	if (tot & 1) {
		cout << "NO\n";
		return;
	}
	for (int i = 1; i <= n; ++i) {
		arr[i] = i;
		pos[arr[i]] = i;
		cnt[i] = n - i;
	}
	vp ans;
	auto f = [&](int x, int y) -> void {
		ans.emplace_back(x, y);
		--cnt[min(x, y)];
		vis[min(x, y)][max(x, y)] = 1;
		swap(pos[arr[x]], pos[arr[y]]);
		swap(arr[x], arr[y]);
	};
	for (int i = 1; i <= n; ++i) {
		if (cnt[i] < 0) {
			cout << "NO\n";
			return;
		}
		if (arr[i] == i) {
			if (cnt[i] == 1) {
				cout << "NO\n";
				return;
			}
			if (cnt[i] == 0) continue;
			vi p;
			for (int j = i + 1; j <= n; ++j) {
				if (!vis[i][j]) p.push_back(j);
			}
			int m = p.size();
			for (int j = 0; j < m - 1; ++j) f(i, p[j]);
			f(p[0], p[m - 1]);
			f(i, p[m - 1]);
		}
		else {
			if (cnt[i] == 0) {
				cout << "NO\n";
				return;
			}
			vi p;
			for (int j = i + 1; j <= n; ++j) {
				if (!vis[i][j]) p.push_back(j);
			}
			int m = p.size();
			if (!vis[i][pos[i]]) {
				for (int v : p) {
					if (v == pos[i]) continue;
					f(i, v);
				}
				f(i, pos[i]);
			}
			else {
				// shouldn't appear?
				cout << "NO\n";
				return;
			}
		}
	}

	assert((int)ans.size() == tot);

	cout << "YES\n";
	for (auto [l, r] : ans) {
		cout << l << ' ' << r << '\n';
	}
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}

