// Problem: G - Alone
// Contest: AtCoder - UNIQUE VISION Programming Contest 2024 Spring(AtCoder Beginner Contest 346)
// URL: https://atcoder.jp/contests/abc346/tasks/abc346_g
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
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
    int n;
    cin >> n;
    vi arr(n + 1);
    int sz = max(1, (int)sqrt(n));
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    int num = (n + sz - 1) / sz;
    vi belong(n + 1);
    vi bl(num + 1);
    vi br(num + 1);
    for (int i = 1; i <= num; ++i) {
        bl[i] = (i - 1) * sz + 1;
        br[i] = min(n, i * sz);
        for (int j = bl[i]; j <= br[i]; ++j) {
            belong[j] = i;
        }
    }

    vi delta(num + 1);
    vii cnt(num + 1, vi(n + 1));
    vi b(n + 1);
    vp last(n + 1);
    ll ans = 0;

    auto pushdown = [&](int block) -> void {
        if (delta[block] == 0) return;
        for (int i = bl[block]; i <= br[block]; ++i) {
            b[i] += delta[block];
            if (b[i] < 0) b[i] = 0;
        }
        delta[block] = 0;
    };

    auto clear = [&](int block) -> void {
        for (int i = bl[block]; i <= br[block]; ++i) {
            if (b[i] + delta[block] > 0) --ans;
            cnt[block][b[i]] = 0;
        }
    };

    // 调用之前必须要保证这里的是真实的值
    auto count = [&](int block) -> void {
        for (int i = bl[block]; i <= br[block]; ++i) {
            ++cnt[block][b[i]];
            if (b[i] > 0) ++ans;
        }
    };

    auto update = [&](int l, int r, int val) -> void {
        if (belong[l] == belong[r]) {
            clear(belong[l]);
            pushdown(belong[l]);
            for (int i = l; i <= r; ++i) {
                b[i] += val;
                if (b[i] < 0) b[i] = 0;
            }
            count(belong[l]);
        }
        else {
            clear(belong[l]);
            clear(belong[r]);
            pushdown(belong[l]);
            pushdown(belong[r]);
            for (int i = l; i <= br[belong[l]]; ++i) {
                b[i] += val;
                if (b[i] < 0) b[i] = 0;
            }
            for (int i = bl[belong[r]]; i <= r; ++i) {
                b[i] += val;
                if (b[i] < 0) b[i] = 0;
            }
            count(belong[l]);
            count(belong[r]);
            for (int i = belong[l] + 1; i < belong[r]; ++i) {
                if (val > 0) {
                    if (delta[i] <= 0) {
                        int idx = abs(delta[i]);
                        if (idx <= n) {
                            ans += cnt[i][idx];
                        }
                    }
                }
                else {
                    if (delta[i] <= 1) {
                        int idx = abs(delta[i] - 1);
                        if (idx <= n) {
                            ans -= cnt[i][idx];
                        }
                    }
                }
                delta[i] += val;
            }
        }
    };

    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        if (last[arr[i]].second == 0) {
            update(1, i, 1);
        }
        else {
            update(last[arr[i]].first + 1, last[arr[i]].second, -1);
            update(last[arr[i]].second + 1, i, 1);
        }
        last[arr[i]] = make_pair(last[arr[i]].second, i);
        // cout << ans << endl;
        // for (int i = 1; i <= num; ++i) {
    		// cout << i << ' ' << delta[i] << '\n';
        // }
        // for (int i = 1; i <= n; ++i) {
        	// cout << b[i] << ' ';
        // }
        // cout << endl;
        res += ans;
    }

    cout << res << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
    return 0;
}