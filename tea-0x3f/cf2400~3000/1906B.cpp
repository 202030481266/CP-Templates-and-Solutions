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

inline constexpr int  MAXN = 500'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;


// 判断性质问题，必然需要寻找关键的洞察
// guess1: n能够划分为 (n + 3) / 2 个组
// guess2: 和能够产生的最多的1有关，和奇偶性有关系
// guess3: 偶数块可以完美的转移，但是奇数块只能不断合并，直到变成偶数然后左移
// guess4: 使用栈可以完美解决这种合并


int cal(const string& s) {
	int n = s.size();
	int p = 0;
	vp arr;
	while (p < n) {
		int i = p + 1;
		while (i < n && s[i] == s[p]) ++i;
		arr.emplace_back(s[p] - '0', i - p);
		p = i;
	}
	int m = arr.size();
	vp st(2);
	int ptr = 0, sum = 0;
	for (int i = 0; i < m; ++i) {
		if (ptr == 0) {
			if (arr[i].first && arr[i].second % 2 == 0) {
				sum += arr[i].second;
			}
			else st[ptr++] = arr[i];
		}
		else {
			if (ptr == 1) {
				if (st[ptr - 1].first) { // (1,
					if (arr[i].first == 0) { // (1 + 0 -> ( / (0
						sum += st[ptr - 1].second + 1;
						ptr = 0;
						if (arr[i].second > 1) {
							st[ptr++] = { arr[i].first, arr[i].second - 1 };
						}
					}
					else {
						if ((arr[i].second + st[ptr - 1].second) % 2 == 0) { // (1 + 1 -> ( / (1
							sum += arr[i].second + st[ptr - 1].second;
							ptr = 0;
						}
						else {
							st[ptr - 1] = { arr[i].first, arr[i].second + st[ptr - 1].second };
						}
					}
				}
				else { // (0 + 0 -> (0
					if (arr[i].first == 0) {
						st[ptr - 1].second += arr[i].second;
					}
					else {
						if (arr[i].second & 1) { // (0 + 1 ->  (0, 1
							st[ptr++] = arr[i];
						}
						else sum += arr[i].second; // (0
					}
				}
			}
			else { // (0, 1
				if (arr[i].first == 0) { // (0, 1 + 0
					int pre = st[ptr - 2].second, one = st[ptr - 1].second;
					if (pre == arr[i].second) {
						ptr = 0;
						st[ptr++] = { 1, pre + arr[i].second + one };
					}
					else if (pre < arr[i].second) {
						sum += pre * 2 + one + 1;
						ptr = 0;
						if (arr[i].second > 1 + pre) {
							st[ptr++] = { arr[i].first, arr[i].second - pre - 1 };
						}
					}
					else {
						sum += arr[i].second * 2 + one - 1;
						ptr = 0;
						st[ptr++] = { 0, pre - arr[i].second };
						st[ptr++] = { 1, 1 };
					}
				}
				else { // (0, 1 + 1
					if ((arr[i].second + st[ptr - 1].second) % 2 == 0) { // (0, 1 + 1 -> (0
						sum += arr[i].second + st[ptr - 1].second;
						--ptr;
					}
					else st[ptr - 1].second += arr[i].second; // (0, 1 + 1 -> (0, 1
				}
			}
		}
	}
	if (ptr && st[ptr - 1].first) {
		if (ptr == 2 && st[ptr - 1].second & 1) ++sum;
		sum += st[ptr - 1].second;
	}
	return sum;
}

// 暴力：BFS建图，返回每个状态所在的连通分量编号
vi bruteGroup(int n) {
	int total = 1 << n;
	vi group(total, -1);
	int gid = 0;
	for (int start = 0; start < total; ++start) {
		if (group[start] != -1) continue;
		// BFS
		queue<int> q;
		q.push(start);
		group[start] = gid;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int i = 0; i < n; ++i) {
				if (v >> i & 1) {  // 选下标i（值为1）
					int nxt = v;
					if (i + 1 < n) nxt ^= 1 << (i + 1);
					if (i - 1 >= 0) nxt ^= 1 << (i - 1);
					if (group[nxt] == -1) {
						group[nxt] = gid;
						q.push(nxt);
					}
				}
			}
		}
		++gid;
	}
	return group;
}

string toStr(int v, int n) {
	string s(n, '0');
	for (int i = 0; i < n; ++i)
		if (v >> i & 1) s[i] = '1';
	return s;
}

void check(int n) {
	vi group = bruteGroup(n);
	int total = 1 << n;
	int err = 0;
	for (int a = 0; a < total; ++a) {
		for (int b = 0; b < total; ++b) {
			string sa = toStr(a, n);
			string sb = toStr(b, n);
			bool bruteAns = (group[a] == group[b]);
			bool fastAns = (cal(sa) == cal(sb));
			if (bruteAns != fastAns) {
				++err;
				cout << "[MISMATCH] n=" << n
					<< " a=" << sa << " b=" << sb
					<< " brute=" << (bruteAns ? "YES" : "NO")
					<< " fast=" << (fastAns ? "YES" : "NO")
					<< "\n";
				if (err >= 20) { cout << "Too many errors, stopping.\n"; return; }
			}
		}
	}
	if (err == 0)
		cout << "n=" << n << " ALL OK (" << total << " states, "
		<< (long long)total * total << " pairs checked)\n";
}

void solve() {
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	if (cal(a) == cal(b)) cout << "YES\n";
	else cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// 对拍模式：检查 n=1..18
	bool CHECK_MODE = false;
	if (CHECK_MODE) {
		for (int n = 1; n <= 10; ++n)
			check(n);
		return 0;
	}

	// 正常做题模式
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}