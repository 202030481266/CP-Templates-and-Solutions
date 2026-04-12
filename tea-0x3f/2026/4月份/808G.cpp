// Problem: G. Anthem of Berland
// Contest: Codeforces - Educational Codeforces Round 21
// URL: https://codeforces.com/problemset/problem/808/G
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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
inline constexpr ll   LL_INFo = numeric_limits<ll>::max() / 2;

// guess1: n*m <= 1e7 ? 肯定是 O(nm) 算法无疑了
// guess2: 考虑kmp，如果在i匹配了，那么下一个匹配的地方就是next[i], dp[i]=max(dp[i-1], dp[next[i]] + 1) if s(next[i], i] can match t

vi build(const string& s) {
    int n = s.size();
    vi next(n);
    int j = 0;
    for (int i = 1; i < n; ++i) {
        while (j > 0 && s[j] != s[i]) j = next[j - 1];
        if (s[j] == s[i]) ++j;
        next[i] = j;
    }
    return next;
}

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    if (n < m) {
        cout << 0 << '\n';
        return;
    }
    vi nxt = build(t);
    vi dp(n);
    vi f(n);
    auto match = [&](int p) -> bool {
        for (int i = p - m + 1, j = 0; i <= p; ++i, ++j) {
            if (s[i] != t[j] && s[i] != '?') return false;
        }
        return true;
    };
    for (int i = m - 1; i < n; ++i) {
        if (i > 0) f[i] = f[i - 1];
        if (match(i)) {
            if (i - m >= 0) {
                dp[i] = max(dp[i], f[i - m] + 1);
                int v = nxt[m - 1];
                while (v > 0) { // has duplicate
                    dp[i] = max(dp[i], dp[i - m + v] + 1);
                    v = nxt[v - 1];
                }
            }
            else dp[i] = max(dp[i], 1);
        }
        f[i] = max(f[i], dp[i]);
    }
    cout << f[n - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}