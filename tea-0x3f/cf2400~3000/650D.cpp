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

inline constexpr int  MAXN = 400005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

int n, m, arr[MAXN];
int pre[MAXN], suf[MAXN];
int px[MAXN], sx[MAXN], ans[MAXN];

struct Q {
	int p, val;
	Q() {}
	Q(int _p, int _val) : p(_p), val(_val) {}
} qs[MAXN];



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


int op(int a, int b) {
	return max(a, b);
}

int e() {
	return 0;
}

void solve() {
	cin >> n >> m;
	vp b;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		b.emplace_back(arr[i], i);
	}
	for (int i = 1; i <= m; ++i) {
		cin >> qs[i].p >> qs[i].val;
		b.emplace_back(qs[i].val, n + i);
	}
	ranges::sort(b);
	int cur = 0;
	for (int i = 0; i < b.size(); ++i) {
		if (i == 0 || b[i].first != b[i - 1].first) ++cur;
		if (b[i].second <= n) arr[b[i].second] = cur;
		else qs[b[i].second - n].val = cur;
	}
	vii pos(n + 1);
	for (int i = 1; i <= m; ++i) {
		pos[qs[i].p].push_back(i);
	}
	segtree<int, op, e> tree(cur + 1);
	for (int i = 1; i <= n; ++i) {
		auto mx = tree.prod(0, arr[i]);
		pre[i] = mx + 1;
		tree.set(arr[i], pre[i]);
		if (i + 1 <= n && !pos[i + 1].empty()) {
			for (int qid : pos[i + 1]) {
				auto res = tree.prod(0, qs[qid].val);
				px[qid] = res;
				ans[qid] = max(ans[qid], tree.all_prod());
			}
		}
	}
	tree = segtree<int, op, e>(cur + 1);
	for (int i = n; i >= 1; --i) {
		auto mx = tree.prod(arr[i] + 1, cur + 1);
		suf[i] = mx + 1;
		tree.set(arr[i], suf[i]);
		if (i - 1 >= 1 && !pos[i - 1].empty()) {
			for (int qid : pos[i - 1]) {
				auto res = tree.prod(qs[qid].val + 1, cur + 1);
				sx[qid] = res;
				ans[qid] = max(ans[qid], tree.all_prod());
			}
		}
	}
	int mx_lis = 0;
	vi can(n + 1, 0);
	int mx_val = 0;
	for (int i = 1; i <= n; ++i) mx_lis = max(mx_lis, suf[i] + pre[i] - 1);
	for (int i = 1; i <= n; ++i) {
		if (suf[i] + pre[i] - 1 == mx_lis) {
			if (arr[i] <= mx_val) can[i] = 1;
			else mx_val = arr[i];
		}
		else can[i] = 1;
	}
	mx_val = INF;
	for (int i = n; i >= 1; --i) {
		if (suf[i] + pre[i] - 1 == mx_lis) {
			if (arr[i] >= mx_val) can[i] = 1;
			else mx_val = arr[i];
		}
		else can[i] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		ans[i] = max(ans[i], px[i] + sx[i] + 1);
		int p = qs[i].p;
		if (can[p]) ans[i] = max(ans[i], mx_lis);
		else ans[i] = max(ans[i], mx_lis - 1);
		cout << ans[i] << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	//cin >> t; 
	while (t--) solve();
	return 0;
}