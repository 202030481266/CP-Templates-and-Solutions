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

inline constexpr int  MAXN = 1000005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;


#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>


#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder {

	namespace internal {

#if __cplusplus >= 202002L

		using std::bit_ceil;

#else

		unsigned int bit_ceil(unsigned int n) {
			unsigned int x = 1;
			while (x < (unsigned int)(n)) x *= 2;
			return x;
		}

#endif

		int countr_zero(unsigned int n) {
#ifdef _MSC_VER
			unsigned long index;
			_BitScanForward(&index, n);
			return index;
#else
			return __builtin_ctz(n);
#endif
		}

		constexpr int countr_zero_constexpr(unsigned int n) {
			int x = 0;
			while (!(n & (1 << x))) x++;
			return x;
		}

	}  // namespace internal

}  // namespace atcoder


namespace atcoder {

#if __cplusplus >= 201703L

	template <class S, auto op, auto e> struct segtree {
		static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
			"op must work as S(S, S)");
		static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
			"e must work as S()");

#else

	template <class S, S(*op)(S, S), S(*e)()> struct segtree {

#endif

	public:
		segtree() : segtree(0) {}
		explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
		explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
			size = (int)internal::bit_ceil((unsigned int)(_n));
			log = internal::countr_zero((unsigned int)size);
			d = std::vector<S>(2 * size, e());
			for (int i = 0; i < _n; i++) d[size + i] = v[i];
			for (int i = size - 1; i >= 1; i--) {
				update(i);
			}
		}

		void set(int p, S x) {
			assert(0 <= p && p < _n);
			p += size;
			d[p] = x;
			for (int i = 1; i <= log; i++) update(p >> i);
		}

		S get(int p) const {
			assert(0 <= p && p < _n);
			return d[p + size];
		}

		S prod(int l, int r) const {
			assert(0 <= l && l <= r && r <= _n);
			S sml = e(), smr = e();
			l += size;
			r += size;

			while (l < r) {
				if (l & 1) sml = op(sml, d[l++]);
				if (r & 1) smr = op(d[--r], smr);
				l >>= 1;
				r >>= 1;
			}
			return op(sml, smr);
		}

		S all_prod() const { return d[1]; }

		template <bool (*f)(S)> int max_right(int l) const {
			return max_right(l, [](S x) { return f(x); });
		}
		template <class F> int max_right(int l, F f) const {
			assert(0 <= l && l <= _n);
			assert(f(e()));
			if (l == _n) return _n;
			l += size;
			S sm = e();
			do {
				while (l % 2 == 0) l >>= 1;
				if (!f(op(sm, d[l]))) {
					while (l < size) {
						l = (2 * l);
						if (f(op(sm, d[l]))) {
							sm = op(sm, d[l]);
							l++;
						}
					}
					return l - size;
				}
				sm = op(sm, d[l]);
				l++;
			} while ((l & -l) != l);
			return _n;
		}

		template <bool (*f)(S)> int min_left(int r) const {
			return min_left(r, [](S x) { return f(x); });
		}
		template <class F> int min_left(int r, F f) const {
			assert(0 <= r && r <= _n);
			assert(f(e()));
			if (r == 0) return 0;
			r += size;
			S sm = e();
			do {
				r--;
				while (r > 1 && (r % 2)) r >>= 1;
				if (!f(op(d[r], sm))) {
					while (r < size) {
						r = (2 * r + 1);
						if (f(op(d[r], sm))) {
							sm = op(d[r], sm);
							r--;
						}
					}
					return r + 1 - size;
				}
				sm = op(d[r], sm);
			} while ((r & -r) != r);
			return 0;
		}

	private:
		int _n, size, log;
		std::vector<S> d;

		void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	};

	}  // namespace atcoder

using namespace atcoder;


vector<tuple<int, int, int>> update_rules;

struct S {
	int dp[32];
	S() {
		memset(dp, 0x3f, sizeof(dp));
	}
};

// bc ab c b a
// 4  3  2 1 0

S op(S a, S b) {
	S res;
	for (auto [u, v, x] : update_rules) {
		res.dp[x] = min(res.dp[x], a.dp[u] + b.dp[v]);
	}
	return res;
}

S e() {
	S s;
	s.dp[0] = 0;
	return s;
}

void solve() {
	int n, m;
	cin >> n >> m;
		segtree<S, op, e> seg(n);
	auto update = [&](int pos, char ch) -> void {
		S tmp;
		tmp.dp[0] = 1;
		if (ch == 'a') tmp.dp[1] = 0;
		else if (ch == 'b') tmp.dp[2] = 0;
		else tmp.dp[4] = 0;
		seg.set(pos, tmp);
	};
	char c;
	for (int i = 0; i < n; ++i) {
		cin >> c;
		update(i, c);
	}
	for (int i = 0, p; i < m; ++i) {
		char c;
		cin >> p >> c;
		--p;
		update(p, c);
		auto res = seg.all_prod();
		int ans = INF;
		for (int i = 0; i < 32; ++i) {
			ans = min(ans, res.dp[i]);
		}
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 32; ++i) {
		if (i >> 3 & 1 && (!(i & 1) || !(i >> 1) & 1)) continue;
		if (i >> 4 & 1 && (!(i >> 1 & 1) || !(i >> 2 & 1))) continue;
		for (int j = 0; j < 32; ++j) {
			if (j >> 3 & 1 && (!(j & 1) || !(j >> 1) & 1)) continue;
			if (j >> 4 & 1 && (!(j >> 1 & 1) || !(j >> 2 & 1))) continue;
			if ((i >> 3 & 1) && (j >> 2 & 1)) continue; // ab + c -> abc
			if (i & 1 && (j >> 4 & 1)) continue; // a + bc -> abc
			int x = i | j;
			if (i & 1 && j >> 1 & 1) x |= 1 << 3; // a + b -> ab
			if (i >> 1 & 1 && j >> 2 & 1) x |= 1 << 4; // b + c -> bc
			//cout << format("{} + {} -> {}\n", i, j, x);
			update_rules.emplace_back(i, j, x);
		}
	}

	int t = 1;
	while (t--) solve();

	return 0;
}