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


static constexpr int dirs[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

void solve() {
	int n, m;
	cin >> n >> m;

	vii a(n, vi(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cin >> a[i][j];
	}
	
	auto f = [&](int x, int y) -> bool {
		if (a[x][y] == 1) return false;
		int mn = INF;
		for (int i = 0; i < 4; ++i) {
			int dx = x + dirs[i][0], dy = y + dirs[i][1];
			if (dx >= 0 && dy >= 0 && dx < n && dy < m) mn = min(mn, a[dx][dy]);
		}
		return mn > a[x][y];
	};

	auto g = [&](int x, int y) -> bool {
		for (int i = 0; i < 4; ++i) {
			int dx = x + dirs[i][0], dy = y + dirs[i][1];
			if (dx >= 0 && dy >= 0 && dx < n && dy < m && f(dx, dy)) return true;
		}
		return false;
	};

	vp arr;
	vii bad(n, vi(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (f(i, j)) {
				bad[i][j] = 1;
				arr.emplace_back(i, j);
			}
		}
	}
	
	if (arr.empty()) {
		cout << 0 << '\n';
		return;
	}
	
	if (arr.size() > 5) {
		cout << 2 << '\n';
		return;
	}

	auto check_swap = [&](int x1, int y1, int x2, int y2) -> bool {
		swap(a[x1][y1], a[x2][y2]);
		bool res = f(x2, y2) || f(x1, y1) || g(x2, y2) || g(x1, y1);
		for (auto [x, y] : arr) {
			res = res || f(x, y);
		}
		swap(a[x1][y1], a[x2][y2]);
		return res;
	};

	// one swaps: 必然是下面的操作中的一个：
	// 1. 将其中一个盆地和另外一个盆地交换
	// 2. 将其中一个盆地和另外一个盆地相邻的块交换
	// 3. 将其中一个盆地相邻的块和不相邻的块交换
	// 4. 将其中一个盆地和不相邻的块交换

	vii vis(n, vi(m));
	vp neib;
	for (auto [x, y] : arr) {
		for (int i = 0; i < 4; ++i) {
			int nx = x + dirs[i][0], ny = y + dirs[i][1];
			if (nx >= 0 && ny >= 0 && nx < n && ny < m && !bad[nx][ny]) { 
				if (!vis[nx][ny]) {
					neib.emplace_back(nx, ny);
				}
				++vis[nx][ny];
			}
		}
	}

	vp c = arr;
	for (auto [x, y] : neib) c.emplace_back(x, y);
	

	int cz = c.size();
	int ans = 0;
	for (int i = 0; i < cz; ++i) {
		for (int j = i + 1; j < cz; ++j) {
			if (!check_swap(c[i].first, c[i].second, c[j].first, c[j].second)) {
				//cout << format("{} {} {} {}\n", c[i].first, c[i].second, c[j].first, c[j].second);
				++ans;
			}
		}
	}

	// 3 + 4
	vp d = arr;
	for (auto [x, y] : neib) {
		if (vis[x][y] == arr.size()) d.emplace_back(x, y);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (bad[i][j] || vis[i][j]) continue;
			for (auto [x, y] : d) {
				if (!check_swap(i, j, x, y)) {
					//cout << format("{} {} {} {}\n", i, j, x, y);
					++ans;
				}
			}
		}
	}

	if (ans > 0) {
		cout << 1 << ' ' << ans << '\n';
	}
	else cout << 2 << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}