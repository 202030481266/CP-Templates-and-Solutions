// Problem: E - E-liter
// Contest: AtCoder - AtCoder Beginner Contest 461
// URL: https://atcoder.jp/contests/abc461/tasks/abc461_e
// Memory Limit: 1024 MB
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
inline constexpr int  MOD_197 = 1'000'000'007;
inline constexpr int  MOD_998 = 998'244'353;
inline constexpr int  MAXB = 30;

class FenwickSet {
private:
    int n, tot;       // n: 值域上限, tot: 当前元素总数
    vector<int> tr;   // 树状数组
    vector<ll> sum;
    int high_bit;     // 倍增搜索的起始位 (2^k)

public:
    FenwickSet(int size) : n(size), tot(0) {
        tr.assign(n + 1, 0);
        sum.assign(n + 1, 0ll);
        high_bit = 1;
        while ((high_bit << 1) <= n) high_bit <<= 1;
    }

    void add(int val, int delta) {
        int s_delta = delta * val;
        tot += delta;
        for (; val <= n; val += val & -val) tr[val] += delta;
        for (; val <= n; val += val & -val) sum[val] += s_delta;
    }

    int ask(int val) {
        int res = 0;
        for (; val > 0; val -= val & -val) res += tr[val];
        return res;
    }

    ll query(int val) {
        ll res = 0;
        for (; val > 0; val -= val & -val) res += sum[val];
        return res;
    }

    // --- 高级接口 ---

    void insert(int val) {
        add(val, 1);
    }

    void erase(int val) {
        if (ask(val) > ask(val - 1)) {
            add(val, -1);
        }
    }

    int kth(int k) {
        if (k > tot) return -1;
        int pos = 0;
        for (int i = high_bit; i > 0; i >>= 1) {
            if (pos + i <= n && tr[pos + i] < k) {
                pos += i;
                k -= tr[pos];
            }
        }
        return pos + 1;
    }

    ll kth_sum(int k) {
        if (k > tot) return -1;
        int pos = 0;
        ll s = 0;
        for (int i = high_bit; i > 0; i >>= 1) {
            if (pos + i <= n && tr[pos + i] < k) {
                pos += i;
                s += sum[pos];
                k -= tr[pos];
            }
        }
        return s + 1ll * k * (pos + 1);
    }

    int get_max() {
        return tot == 0 ? -1 : kth(tot);
    }

    int get_min() {
        return tot == 0 ? -1 : kth(1);
    }

    int size() { return tot; }
};

void solve() {
    int n, q;
    
    cin >> n >> q;

    vi black(n + 1, -1);
    vi white(n + 1, -1);

    FenwickSet row(q + 1);
    FenwickSet col(q + 1);

    ll ans = 0;
    for (int i = 1, op, x; i <= q; ++i) {
        cin >> op >> x;
        if (op == 1) {
            if (black[x] != -1) {
                ans += col.ask(q) - col.ask(black[x]); // 减去所有的 >= last[x] 的 column operation
                row.add(black[x], -1);
            }
            else {
                ans += n;
            }
            black[x] = i;
            row.add(black[x], 1);
        }
        else {
            if (white[x] != -1) {
                ans -= row.ask(q) - row.ask(white[x]);
                col.add(white[x], -1);
            }
            else {
                ans -= row.ask(q);
            }
            white[x] = i;
            col.add(white[x], 1);
        }

        cout << ans << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}