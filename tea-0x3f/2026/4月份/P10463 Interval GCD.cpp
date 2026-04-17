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
inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

// 分块 + 懒标记处理
inline constexpr int MAXB = 710;

int bl[MAXB], br[MAXB];
int belong[MAXN];
ll pre[MAXB];
ll lazy[MAXB];
ll arr[MAXN];

void reCalPre(int b) {
    for (int i = bl[b]; i <= br[b]; ++i) arr[i] += lazy[b];
    lazy[b] = 0;
    pre[b] = 0;
    for (int i = bl[b] + 1; i <= br[b]; ++i) {
        pre[b] = gcd(pre[b], arr[i] > arr[bl[b]] ? arr[i] - arr[bl[b]] : arr[bl[b]] - arr[i]);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    int block_size = max(1, static_cast<int>(sqrt(n)));
    int block_num = (n + block_size - 1) / block_size;
    for (int i = 1; i <= block_num; ++i) {
        bl[i] = (i - 1) * block_size + 1;
        br[i] = min(n, i * block_size);
        for (int j = bl[i]; j <= br[i]; ++j) belong[j] = i;
        reCalPre(i);
    }
    char op;
    ll d;
    for (int q = 1, l, r; q <= m; ++q) {
        cin >> op;
        if (op == 'C') {
            cin >> l >> r >> d;
            if (belong[r] <= belong[l] + 1) {
                for (int i = l; i <= r; ++i) arr[i] += d;
            }
            else {
                for (int i = l; i <= br[belong[l]]; ++i) arr[i] += d;
                for (int i = belong[l] + 1; i < belong[r]; ++i) lazy[i] += d;
                for (int i = bl[belong[r]]; i <= r; ++i) arr[i] += d;
            }
            reCalPre(belong[l]);
            if (belong[r] > belong[l]) reCalPre(belong[r]);
        }
        else {
            cin >> l >> r;
            ll g = 0;
            if (belong[r] <= belong[l] + 1) {
                for (int i = l; i <= r; ++i) g = gcd(g, arr[i] + lazy[belong[i]]);
            }
            else {
                for (int i = l; i <= br[belong[l]]; ++i) g = gcd(g, arr[i] + lazy[belong[i]]);
                for (int i = belong[l] + 1; i < belong[r]; ++i) g = gcd(g, gcd(arr[bl[i]] + lazy[i], pre[i]));
                for (int i = bl[belong[r]]; i <= r; ++i) g = gcd(g, arr[i] + lazy[belong[i]]);
            }
            cout << g << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}