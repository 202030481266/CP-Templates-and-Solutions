// Problem: D. Buy Low Sell High
// Contest: Codeforces - MemSQL Start[c]UP 3.0 - Round 2 (onsite finalists)
// URL: https://codeforces.com/problemset/problem/865/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

// 本质上就是你有一堆股票，然后每天就是卖股票（永远不需要买，用一个堆维护），每一次选择最小的卖掉

void solve() {
    int n;
    cin >> n;
    vi arr(n);
    for (int i = 0 ; i < n; ++i) {
        cin >> arr[i];
    }

    priority_queue<int, vi, greater<int>> q1;
    priority_queue<int, vi, greater<int>> q2;

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!q1.empty() || !q2.empty()) {
            if (!q1.empty() && !q2.empty()) {
                int x = q1.top();
                int y = q2.top();
                if (arr[i] <= min(x, y)) {
                    q1.push(arr[i]);
                }
                else {
                    if (x < y) {
                        q1.pop();
                        ans += arr[i] - x;
                        q2.push(arr[i]);
                    }
                    else {
                        q2.pop();
                        ans += arr[i] - y;
                        q1.push(y);
                        q2.push(arr[i]);
                    }
                }
            }
            else if (!q1.empty()) {
                if (q1.top() < arr[i]) {
                    int x = q1.top();
                    q1.pop();
                    ans += arr[i] - x;
                    q2.push(arr[i]);
                }
                else q1.push(arr[i]);
            }
            else {
                if (q2.top() < arr[i]) {
                    int x = q2.top();
                    q2.pop();
                    q1.push(x);
                    ans += arr[i] - x;
                    q2.push(arr[i]);
                }
                else q1.push(arr[i]);
            }
        }
        else q1.push(arr[i]);
    }

    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}