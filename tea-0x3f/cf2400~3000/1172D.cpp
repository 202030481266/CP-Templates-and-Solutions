// Problem: D. Nauuo and Portals
// Contest: Codeforces - Codeforces Round 564 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1172/D
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

	vi row(n + 1);
	vi col(n + 1);
	for (int i = 1; i <= n; ++i) cin >> row[i];
	for (int i = 1; i <= n; ++i) cin >> col[i];

	auto f = [](vi& a) -> vp {
		int n = (int)a.size() - 1;
		vi vis(n + 1);
		vi pos(n + 1);
		for (int i = 1; i <= n; ++i) pos[a[i]] = i;
		vp res;
		for (int i = 1; i <= n; ++i) {
			int cur = i;
			while (!vis[cur]) {
				vis[cur] = 1;
				int x = a[a[cur]];
				if (x == cur) break;
				else {
					int p = pos[cur];
					res.emplace_back(min(p, a[cur]), max(p, a[cur]));
					swap(pos[cur], pos[x]);
					swap(a[p], a[a[cur]]);
					cur = p;
				}
			}
		}
		return res;
	};

	auto r = f(row);
	auto c = f(col);
	ranges::sort(r);
	ranges::sort(c);

	vp pr, pc;
	for (int i = 1; i <= n; ++i) {
		if (row[i] > i) pr.emplace_back(i, row[i]);
		if (col[i] > i) pc.emplace_back(i, col[i]);
	}

	vi vr(n + 1), vc(n + 1);
	int N = pr.size(), M = pc.size();
	vp ans;
	for (int i = 0; i < min(N, M); ++i) {
		ans.emplace_back(pr[i].first, pc[i].first);
		ans.emplace_back(pr[i].second, pc[i].second);
		vr[pr[i].first] = 1;
		vr[pr[i].second] = 1;
		vc[pc[i].first] = 1;
		vc[pc[i].second] = 1;
	}

	if (N > M) {
		int col = 0;
		for (int i = 2; i <= n; ++i) {
			if (!vc[i]) {
				col = i;
				break;
			}
		}
		assert(col > 0);
		for (int i = M; i < N; ++i) {
			ans.emplace_back(pr[i].first, col);
			ans.emplace_back(pr[i].second, col);
		}
	}

	if (N < M) {
		int row = 0;
		for (int i = 2; i <= n; ++i) {
			if (!vr[i]) {
				row = i;
				break;
			}
		}
		assert(row > 0);
		for (int i = N; i < M; ++i) {
			ans.emplace_back(row, pc[i].first);
			ans.emplace_back(row, pc[i].second);
		}
	}

	for (auto [u, v] : r) {
		ans.emplace_back(u, 1);
		ans.emplace_back(v, 1);
	}
	for (auto [u, v] : c) {
		ans.emplace_back(1, u);
		ans.emplace_back(1, v);
	}

	n = ans.size();
	cout << n / 2 << '\n';
	for (int i = 0; i < n; i += 2) {
		cout << ans[i].first << ' ' << ans[i].second << ' ' << ans[i + 1].first << ' ' << ans[i + 1].second << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}