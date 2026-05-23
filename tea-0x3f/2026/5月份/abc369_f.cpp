// Problem: D. A Simple Task
// Contest: Codeforces - Codeforces Beta Round 11
// URL: https://codeforces.com/problemset/problem/11/D
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

struct Node {
	int max_val;
	int max_idx;
};

class FenwickTree {
private:
	vector<Node> tree;
	int n;

	int lowbit(int x) {
		return x & (-x);
	}

public:
	FenwickTree(int size) {
		n = size;
		tree.assign(n + 1, { 0, -1 });
	}

	void update(int i, int val, int original_idx) {
		for (; i <= n; i += lowbit(i)) {
			if (val > tree[i].max_val) {
				tree[i].max_val = val;
				tree[i].max_idx = original_idx;
			}
		}
	}

	Node query(int i) {
		Node res = { -1000000000, -1 };
		for (; i > 0; i -= lowbit(i)) {
			if (tree[i].max_val > res.max_val) {
				res.max_val = tree[i].max_val;
				res.max_idx = tree[i].max_idx;
			}
		}
		return res;
	}
};

void solve() {
	int h, w, n;
	cin >> h >> w >> n;

	n += 2;
	vp arr(n);
	vp b;
	arr[0] = { 1, 1 };
	arr[1] = { h, w };
	b.emplace_back(1, 0);
	b.emplace_back(w, 1);
	for (int i = 2; i < n; ++i) {
		cin >> arr[i].first >> arr[i].second;
		b.emplace_back(arr[i].second, i);
	}

	ranges::sort(b);
	int cur = 0;
	vi rk(n + 1);
	for (int i = 0; i < n; ++i) {
		if (i == 0 || b[i].first != b[i - 1].first) {
			++cur;
			rk[cur] = b[i].first;
		}
		arr[b[i].second].second = cur;
	}

	ranges::sort(arr);

	FenwickTree f(cur + 1);
	vi pre(n, -1);
	vi dp(n, 0);

	int p = 0;
	while (p < n) {
		int i = p + 1;
		while (i < n && arr[i].first == arr[p].first) ++i;
		for (int j = p; j < i; ++j) {
			Node res = f.query(arr[j].second);
			dp[j] = res.max_val + 1;
			pre[j] = res.max_idx;
		}
		for (int j = p; j < i; ++j) {
			if (j > p && dp[j] < dp[j - 1] + 1) {
				dp[j] = dp[j - 1] + 1;
				pre[j] = j - 1;
			}
			f.update(arr[j].second, dp[j], j);
		}
		p = i;
	}

	cout << dp[n - 1] - 2 << '\n';
	int x = n - 1;
	vec<char> ans;
	while (pre[x] != -1) {
		// cout << x << ' ' << pre[x] << endl;
		int pos = pre[x];
		int dx = arr[x].first - arr[pos].first;
		int dy = rk[arr[x].second] - rk[arr[pos].second];
		for (int i = 0; i < dx; ++i) ans.push_back('D');
		for (int i = 0; i < dy; ++i) ans.push_back('R');
		x = pos;
	}
	for (int i = (int)ans.size() - 1; i >= 0; --i) cout << ans[i];
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}