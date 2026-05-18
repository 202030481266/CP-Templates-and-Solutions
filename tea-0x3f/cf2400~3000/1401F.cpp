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

int n, q;
ll arr[MAXN];
ll sum[MAXN << 2];
ll flag[20];

void build(int rt, int l, int r) {
	if (l == r) {
		sum[rt] = arr[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

ll query(int rt, int l, int r, int L, int R, int layer) {
	if (L <= l && r <= R) return sum[rt];
	int mid = (l + r) >> 1;
	int offset = mid - l + 1;
	if (R <= mid) {
		if (flag[layer]) {
			return query(rt << 1 | 1, mid + 1, r, L + offset, R + offset, layer - 1);
		}
		return query(rt << 1, l, mid, L, R, layer - 1);
	}
	else if (L > mid) {
		if (flag[layer]) {
			return query(rt << 1, l, mid, L - offset, R - offset, layer - 1);
		}
		return query(rt << 1 | 1, mid + 1, r, L, R, layer - 1);
	}
	else {
		if (flag[layer]) {
			return query(rt << 1 | 1, mid + 1, r, L + offset, mid + offset, layer - 1) +
				query(rt << 1, l, mid, mid + 1 - offset, R - offset, layer - 1);
		}
		return query(rt << 1, l, mid, L, mid, layer - 1) + query(rt << 1 | 1, mid + 1, r, mid + 1, R, layer - 1);
	}
}

void modify(int rt, int l, int r, int p, ll val, int layer) {
	if (l == r) {
		sum[rt] = val;
		return;
	}
	int mid = (l + r) >> 1;
	int offset = mid - l + 1;
	if (p <= mid) {
		if (flag[layer]) modify(rt << 1 | 1, mid + 1, r, p + offset, val, layer - 1);
		else modify(rt << 1, l, mid, p, val, layer - 1);
	}
	else {
		if (flag[layer]) modify(rt << 1, l, mid, p - offset, val, layer - 1);
		else modify(rt << 1 | 1, mid + 1, r, p, val, layer - 1);
	}
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= 1 << n; ++i) cin >> arr[i];
	build(1, 1, 1 << n);
	for (int i = 0, op, x, k; i < q; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> x >> k;
			modify(1, 1, 1 << n, x, k, n);
		}
		else if (op == 2) {
			cin >> k;
			for (int j = k; j >= 0; --j) flag[j] ^= 1;
		}
		else if (op == 3) {
			cin >> k;
			flag[k + 1] ^= 1;
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << query(1, 1, 1 << n, l, r, n) << '\n';
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}