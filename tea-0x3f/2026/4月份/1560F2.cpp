// Problem: F2. Nearest Beautiful Number (hard version)
// Contest: Codeforces - Codeforces Round 739 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1560/F2
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

long long pw[15];

int getSmall(int x) {
    if (x == 0) return INF;
    int low = x & -x;
    return bit_width(1u * low) - 1;
}

void solve() {
    int n, k;
    cin >> n >> k;
    string s = to_string(n);
    n = s.size();
    ll ans = pw[n] - 1, cur = 0;
    int mask = 0;
    for (int i = 0; i < n; ++i) {
        int d = s[i] - '0', ones = popcount(1u * mask), p = getSmall(mask);
        if (ones > k) break;
        if (d < 9) {
            if (mask) {
                for (int x = d + 1; x <= 9; ++x) {
                    if (mask >> x & 1) {
                        if (ones < k) ans = min(ans, cur + x * pw[n - i - 1]);
                        else {
                            ll t = cur + x * pw[n - i - 1];
                            for (int j = i + 1; j < n; ++j) t += p * pw[n - j - 1];
                            ans = min(ans, t);
                        }
                        break;
                    }
                }
            }
            if (!(mask >> d + 1 & 1) && ones < k) {
                ll t = cur + (d + 1) * pw[n - i - 1];
                if (ones + 1 < k) ans = min(ans, t);
                else {
                    for (int j = i + 1; j < n; ++j) t += min(p, d + 1) * pw[n - j - 1];
                    ans = min(ans, t);
                }
            }
        }
        mask |= 1 << d;
        cur += d * pw[n - i - 1];
    }
    if (popcount(1u * mask) <= k) ans = min(ans, cur);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    pw[0] = 1;
    for (int i = 1; i <= 12; ++i) pw[i] = pw[i - 1] * 10;

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}