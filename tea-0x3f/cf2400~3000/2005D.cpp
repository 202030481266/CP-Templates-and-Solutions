// Problem: D. Alter the GCD
// Contest: Codeforces - Codeforces Round 972 (Div. 2)
// URL: https://codeforces.com/problemset/problem/2005/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

template<typename T>
concept Element = std::copyable<T>;

template<typename Op, typename T>
concept IdempotentOp = requires(Op op, T a, T b) {
	{ op(a, b) } -> std::convertible_to<T>;
};

template<Element T, typename Op>
requires IdempotentOp<Op, T>
class SparseTable {
public:
    SparseTable() = default;

    explicit SparseTable(std::vector<T> const& a, Op op = {})
        : n_(a.size()), op_(op) 
    {
        int LOG = std::bit_width(static_cast<unsigned>(n_));
        table_.assign(LOG * n_, 0); 
        for (int i = 0; i < n_; ++i) table_[i] = a[i];
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i + (1 << j) <= n_; ++i) {
                table_[j * n_ + i] = op_(table_[(j - 1) * n_ + i], table_[(j - 1) * n_ + i + (1 << (j - 1))]);
            }
        }
        log_.resize(n_ + 1);
        log_[1] = 0;
        for (int i = 2; i <= n_; ++i) log_[i] = log_[i / 2] + 1;
    }

    T query(int l, int r) const {
        int k = log_[r - l + 1];
        return op_(table_[k * n_ + l], table_[k * n_ + r - (1 << k) + 1]);
    }

    int size() const { return n_; }

private:
    int n_ = 0;
    Op op_;
    std::vector<T> table_;
    std::vector<int> log_;
};

struct Gcd {
	template<typename T>
	T operator()(T a, T b) const { return std::gcd(a, b); }
};

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    
    SparseTable<int, Gcd> sa(a);
    SparseTable<int, Gcd> sb(b);
    
    vi suf_a(n + 1, 0), suf_b(n + 1, 0); 
    for (int i = n - 1; i >= 0; --i) {
        suf_a[i] = gcd(suf_a[i + 1], a[i]);
        suf_b[i] = gcd(suf_b[i + 1], b[i]);
    }
    
    ll ans = 0, mx = 0;
    int pre_a = 0, pre_b = 0; 
    
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            pre_a = gcd(pre_a, a[i - 1]);
            pre_b = gcd(pre_b, b[i - 1]);
        }
        
        int ptr = i;
        int ca = gcd(b[i], pre_a), cb = gcd(a[i], pre_b);
        
        while (ptr < n && ca + cb >= mx) {
            int l = ptr, r = n;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                int nca = gcd(pre_a, sb.query(i, mid));
                int ncb = gcd(pre_b, sa.query(i, mid));
                if (nca == ca && ncb == cb) l = mid;
                else r = mid;
            }
            
            int mx_a = gcd(ca, suf_a[l + 1]); 
            int mx_b = gcd(cb, suf_b[l + 1]);
            int mx_left_p = l;
            
            r = l + 1;
            l = ptr;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                int nca = gcd(ca, suf_a[mid]);
                int ncb = gcd(cb, suf_b[mid]);
                if (nca == mx_a && ncb == mx_b) r = mid;
                else l = mid;
            }
            
            if (mx_a + mx_b > mx) {
                mx = mx_a + mx_b;
                ans = mx_left_p + 1 - r + 1;
            }
            else if (mx_a + mx_b == mx) ans += mx_left_p + 1 - r + 1;
            
            ptr = mx_left_p + 1;
            if (ptr < n) {
                ca = gcd(pre_a, sb.query(i, ptr));
                cb = gcd(pre_b, sa.query(i, ptr));
            }
        }
    }
    cout << mx << ' ' << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}