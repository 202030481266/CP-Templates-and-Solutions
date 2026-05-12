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

struct DSU {
	vector<int> par, rnk, sz;
	int c;
	DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
		iota(par.begin(), par.end(), 0);
	}
	int find(int i) {
		return (par[i] == i ? i : (par[i] = find(par[i])));
	}
	bool same(int i, int j) {
		return find(i) == find(j);
	}
	int get_size(int i) {
		return sz[find(i)];
	}
	int count() {
		return c;
	}
	int merge(int i, int j) {
		if ((i = find(i)) == (j = find(j)))
			return -1;
		else
			--c;
		if (rnk[i] > rnk[j])
			swap(i, j);
		par[i] = j;
		sz[j] += sz[i];
		if (rnk[i] == rnk[j])
			rnk[j]++;
		return j;
	}
};

struct StackArray {
	vector<int> head, next, val;
	StackArray(int max_lists, int max_elements) {
		head.assign(max_lists, -1);
		next.reserve(max_elements);
		val.reserve(max_elements);
	}
	void push(int list_idx, int v) {
		val.push_back(v);
		next.push_back(head[list_idx]);
		head[list_idx] = val.size() - 1;
	}
	void pop(int list_idx) {
		head[list_idx] = next[head[list_idx]];
	}
	int back(int list_idx) const {
		return val[head[list_idx]];
	}
	bool empty(int list_idx) const {
		return head[list_idx] == -1;
	}
};

class NaturalArrayCP {
private:
	struct Node {
		int max_val;
		int lazy;
	};
	vector<Node> tree;
	priority_queue<int> pq, del_pq;
	int limit;

	inline void push_up(int node) {
		tree[node].max_val = max(tree[node << 1].max_val, tree[(node << 1) | 1].max_val);
	}

	inline void push_down(int node) {
		if (tree[node].lazy != 0) {
			int laz = tree[node].lazy;
			int lc = node << 1;
			int rc = lc | 1;

			tree[lc].max_val += laz;
			tree[lc].lazy += laz;
			tree[rc].max_val += laz;
			tree[rc].lazy += laz;

			tree[node].lazy = 0;
		}
	}

	void build(int node, int l, int r) {
		tree[node].lazy = 0;
		if (l == r) {
			tree[node].max_val = l - 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(node << 1, l, mid);
		build((node << 1) | 1, mid + 1, r);
		push_up(node);
	}

	void update(int node, int l, int r, int ql, int qr, int val) {
		if (ql <= l && r <= qr) {
			tree[node].max_val += val;
			tree[node].lazy += val;
			return;
		}
		push_down(node);
		int mid = (l + r) >> 1;
		if (ql <= mid) update(node << 1, l, mid, ql, qr, val);
		if (qr > mid)  update((node << 1) | 1, mid + 1, r, ql, qr, val);
		push_up(node);
	}

	int query_max(int node, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return tree[node].max_val;
		}
		push_down(node);
		int mid = (l + r) >> 1;
		int res = -2e9;
		if (ql <= mid) res = max(res, query_max(node << 1, l, mid, ql, qr));
		if (qr > mid)  res = max(res, query_max((node << 1) | 1, mid + 1, r, ql, qr));
		return res;
	}

	inline int get_max() {
		while (!del_pq.empty() && pq.top() == del_pq.top()) {
			pq.pop();
			del_pq.pop();
		}
		return pq.empty() ? -1 : pq.top();
	}

public:
	NaturalArrayCP(const vector<int>& a) {
		limit = 1;
		for (int x : a) if (x > limit) limit = x;

		tree.resize((limit + 1) * 4);
		build(1, 1, limit);

		for (int x : a) {
			if (x > 0) {
				pq.push(x);
				update(1, 1, limit, 1, x, 1);
			}
		}
	}

	void pop_val(int val) {
		int M = get_max();
		if (M == -1) return;

		del_pq.push(M);
		update(1, 1, limit, 1, M, -1);

		int new_val = M - val;
		if (new_val > 0) {
			pq.push(new_val);
			update(1, 1, limit, 1, new_val, 1);
		}
	}

	pair<int, int> query() {
		int M = get_max();
		if (M == -1) return { -1, -1 };
		int max_index = query_max(1, 1, limit, 1, M);
		return { M, max_index };
	}
};

void solve() {
	int n;
	cin >> n;
	vi a(n), b(n);
	for (int& v : a) cin >> v;
	for (int& v : b) cin >> v;

	vi ia(n), ib(n);
	iota(ia.begin(), ia.end(), 0);
	iota(ib.begin(), ib.end(), 0);
	ranges::sort(ia, [&](int i, int j) { return a[i] < a[j]; });
	ranges::sort(ib, [&](int i, int j) { return b[i] < b[j]; });

	vi aa(n * 2 + 5, 0);
	vi bb(n * 2 + 5, 0);
	int p = 1;
	for (int i = 0; i < n; ++i) {
		if (p < a[ia[i]]) p = a[ia[i]];
		aa[p++] = ia[i] + 1;
	}
	p = 1;
	for (int i = 0; i < n; ++i) {
		if (p < b[ib[i]]) p = b[ib[i]];
		bb[p++] = ib[i] + 1;
	}

	ll sa = 0, sb = 0;
	int pp = 0;
	for (int i = 1; i < 2 * n + 2; ++i) {
		sa += aa[i] > 0 ? 1 : 0;
		sb += bb[i] > 0 ? 1 : 0;
		if (sa && sb && sa + sb >= i + 1) {
			pp = i;
			break;
		}
	}
	if (pp == 0) {
		cout << -1 << '\n';
		return;
	}

	StackArray ca(n + 5, 3 * n);
	StackArray cb(n + 5, 3 * n);
	vi init_a, init_b;
	init_a.reserve(n);
	init_b.reserve(n);

	for (int i = 1; i <= pp; ++i) {
		if (aa[i]) {
			ca.push(a[aa[i] - 1], aa[i]);
			init_a.push_back(a[aa[i] - 1]);
		}
		if (bb[i]) {
			cb.push(b[bb[i] - 1], bb[i] + n);
			init_b.push_back(b[bb[i] - 1]);
		}
	}

	NaturalArrayCP tree_a(init_a);
	NaturalArrayCP tree_b(init_b);
	int pa = n, pb = n;
	DSU dsu(2 * n);

	for (int i = pp; i >= 1; --i) {
		while (pa >= 1 && ca.empty(pa)) --pa;
		while (pb >= 1 && cb.empty(pb)) --pb;

		auto [_, mx_a_index] = tree_a.query();
		auto [_, mx_b_index] = tree_b.query();

		if (mx_a_index > i) {
			tree_a.pop_val(INF);
			ca.pop(pa);
			++i;
			continue;
		}

		if (mx_b_index > i) {
			tree_b.pop_val(INF);
			cb.pop(pb);
			++i;
			continue;
		}

		if (mx_a_index == i && mx_b_index == i) {
			int x = ca.back(pa); ca.pop(pa);
			int y = cb.back(pb); cb.pop(pb);
			int f = dsu.merge(x, y);

			tree_a.pop_val(pb);
			tree_b.pop_val(pa);

			if (pa == pb) {
				vi ra, rb;
				ra.reserve(n); rb.reserve(n);
				for (int j = 1; j <= n; ++j) {
					if (dsu.same(j, f)) ra.push_back(j);
				}
				for (int j = n + 1; j <= 2 * n; ++j) {
					if (dsu.same(j, f)) rb.push_back(j - n);
				}
				cout << ra.size() << '\n';
				for (int v : ra) cout << v << ' ';
				cout << '\n';
				cout << rb.size() << '\n';
				for (int v : rb) cout << v << ' ';
				cout << '\n';
				return;
			}
			else if (pa > pb) {
				ca.push(pa - pb, f);
			}
			else {
				cb.push(pb - pa, f);
			}
		}
		else if (mx_a_index == i) {
			ca.pop(pa);
			tree_a.pop_val(INF);
		}
		else if (mx_b_index == i) {
			cb.pop(pb);
			tree_b.pop_val(INF);
		}
	}
	cout << -1 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}