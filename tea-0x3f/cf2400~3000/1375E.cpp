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

inline constexpr int  MAXN = 100005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

// 暴力方法（不限制原始的数组）：不断找到逆序对(a[i], a[j])，其中(i,j)中的数字都是大于max(a[i],a[j])或者小于min(a[i],a[j])的
// guess1: 只需要找到最小差值的 inversion 来swap就行了，维护一下 delta 
// guess2: 一定存在差值为 1 的 inversion ? 比方说 (x, x-2)，那么 x-1 无论放到哪里都会形成一个差值为 1 的逆序对
// 需要知道怎么维护这些差值？不对，我怎么感觉存在一种顺序能够全部完美做掉，应该就是不断找(x+1,x)就可以了
// 3 1 5 4 2 {(3,2),(5,4)}
// (3,2) -> 2 1 5 4 3 {(5,4),(1,2),(4,3)}
// (5,4) -> 2 1 4 5 3 {(1,2),(4,3)}
// (1,2) -> 1 2 4 5 3 {(4,3)}
// (4,3) -> 1 2 3 5 4 {(4,5)}
// (4,5) -> 1 2 3 4 5 {}

void solve() {
	int n;
	cin >> n;

	vi arr(n);
	for (int& v : arr) cin >> v;

	if (is_sorted(arr.begin(), arr.end())) {
		cout << 0 << '\n';
		return;
	}

	vp b;
	for (int i = 0; i < n; ++i) b.emplace_back(arr[i], i);
	ranges::sort(b);
	for (int i = 0; i < n; ++i) {
		arr[b[i].second] = i;
	}

	vi pos(n, INF);
	queue<pii> q;
	for (int i = 0; i < n; ++i) {
		pos[arr[i]] = i;
		if (arr[i] + 1 < n && pos[arr[i] + 1] < i) q.emplace(arr[i] + 1, arr[i]);
	}

	vp ans;
	while (!q.empty()) {
		auto [u, v] = q.front();
		q.pop();
		// (u, u-1) -> (u-1, u)
		int pu = pos[u];
		int pv = pos[v];
		pos[u] = pv;
		pos[v] = pu;
		swap(arr[pu], arr[pv]);
		ans.emplace_back(pu, pv);
		if (u + 1 < n && pos[u + 1] > pu && pos[u + 1] < pv) q.emplace(u + 1, u);
		if (v > 0 && pos[v - 1] > pu && pos[v - 1] < pv) q.emplace(v, v - 1);
	}

	cout << ans.size() << '\n';
	for (auto [u, v] : ans) {
		cout << min(u, v) + 1 << ' ' << max(u, v) + 1 << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}
