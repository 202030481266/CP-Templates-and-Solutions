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

// dp[i] = max(dp[j]) + 1 if check(j, i)
// DAG的思路没有问题，但是状态不止104种，而是 52 * 2 ^ n 种，也就是 1024 * 52 = 53248 种，代表了所有可能的拦截线
// 52 * 52 * 1024 = 2768896 = 3 * 10^6 的复杂度

void solve() {
	int n;
	cin >> n;
	vii grid(n);
	vii pos(n, vi(104, -1));
	vi cnt(104);
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		grid[i].resize(s.size());
		for (int j = 0; j < s.size(); ++j) {
			if (islower(s[j])) grid[i][j] = s[j] - 'a';
			else grid[i][j] = s[j] - 'A' + 26;
		}
	}
	for (int i = 0; i < n; ++i) {
		fill(cnt.begin(), cnt.end(), 0);
		for (int j = 0; j < grid[i].size(); ++j) {
			if (cnt[grid[i][j]]) {
				pos[i][52 + grid[i][j]] = j;
			}
			else {
				cnt[grid[i][j]] = 1;
				pos[i][grid[i][j]] = j;
			}
		}
	}
	vi exist(104, 1);
	for (int i = 0; i < 104; ++i) {
		for (int j = 0; j < n; ++j) {
			if (pos[j][i] == -1) {
				exist[i] = 0;
				break;
			}
		}
	}
	int N = 1 << n;
	vii g(52 * N);
	vi d(52 * N);
	vi dp(52 * N);
	vi pre(52 * N, -1);
	for (int i = 0; i < 52; ++i) {
		if (!exist[i]) continue;
		for (int status = 0; status < 1 << n; ++status) {
			bool flag = 1;
			vi c;
			for (int k = 0; k < n; ++k) {
				if ((status >> k & 1) && pos[k][52 + i] == -1) {
					flag = 0;
					break;
				}
				if (status >> k & 1) c.push_back(pos[k][52 + i]);
				else c.push_back(pos[k][i]);
			}
			if (!flag) continue;
			dp[i * N + status] = 1;
			int pre_status = 0;
			for (int j = 0; j < 52; ++j) { // 这里已经处理了相同字符的状态转移了
				if (!exist[j]) continue;
				flag = 1;
				pre_status = 0;
				for (int k = 0; k < n; ++k) {
					if (pos[k][j + 52] != -1 && pos[k][j + 52] < c[k]) pre_status |= 1 << k;
					else if (pos[k][j] >= c[k]) {
						flag = 0;
						break;
					}
				}
				if (flag) {
					g[j * N + pre_status].push_back(i * N + status);
					++d[i * N + status];
				}
			}
		}
	}
	queue<int> q;
	for (int i = 0; i < 52; ++i) {
		for (int j = 0; j < N; ++j) {
			if (dp[i * N + j] && d[i * N + j] == 0) q.push(i * N + j);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : g[u]) {
			--d[v];
			if (dp[u] + 1 > dp[v]) {
				dp[v] = dp[u] + 1;
				pre[v] = u;
			}
			if (d[v] == 0) q.push(v);
		}
	}
	int cur = -1, mx = 0;
	string ans;
	for (int i = 0; i < 52 * N; ++i) {
		if (dp[i] > mx) {
			mx = dp[i];
			cur = i;
		}
	}
	while (cur != -1) {
		int ch = cur / N;
		ans.push_back(ch >= 26 ? 'A' + ch - 26 : 'a' + ch);
		cur = pre[cur];
	}
	reverse(ans.begin(), ans.end());
	cout << mx << '\n' << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t; 
	while (t--) solve();
	return 0;
}