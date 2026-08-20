// Problem: E. The Turtle Strikes Back
// Contest: Codeforces - Codeforces Round 1078 (Div. 2)
// URL: https://codeforces.com/problemset/problem/2194/E
// Memory Limit: 512 MB
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


void solve() {
    int n, m;
    cin >> n >> m;    

    vii arr(n + 1, vi(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> arr[i][j];
        }
    }

    vll f(n + 2, vl(m + 2, -LLINF));
    vll g(n + 2, vl(m + 2, -LLINF));
    f[1][0] = 0;
    f[0][1] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]) + arr[i][j];
        }
    }
    g[n][m + 1] = 0;
    g[n + 1][m] = 0;
    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            g[i][j] = max(g[i + 1][j], g[i][j + 1]) + arr[i][j];
        }
    }
    
    vll mx1(n + 2, vl(m + 2));
    vll mx2(n + 2, vl(m + 2));
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            mx1[i][j] = f[i][j] + g[i][j] - arr[i][j];
            if (j > 1) mx1[i][j] = max(mx1[i][j], mx1[i][j - 1]);
            if (i < n) mx1[i][j] = max(mx1[i][j], mx1[i + 1][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            mx2[i][j] = f[i][j] + g[i][j] - arr[i][j];
            if (j < m) mx2[i][j] = max(mx2[i][j], mx2[i][j + 1]);
            if (i > 1) mx2[i][j] = max(mx2[i][j], mx2[i - 1][j]);
        }
    }
    
    ll ans = LLINF;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ll mx = -LLINF;
            if (i > 1 && j < m) mx = max(mx, mx2[i - 1][j + 1]);
            if (i < n && j > 1) mx = max(mx, mx1[i + 1][j - 1]);
            ll res = f[i][j] + g[i][j] - 1ll * 3 * arr[i][j];
            ans = min(ans, max(res, mx));
        }
    }
    
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}