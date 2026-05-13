// Problem: E. Divisive Battle
// Contest: Codeforces - Codeforces Round 1084 (Div. 3)
// URL: https://codeforces.com/problemset/problem/2200/E
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
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

pair<vector<int>, vector<bool>> get_primes(int n) {
    if (n <= 1)
        return {};
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    for (int i = 2; i * i <= n; i++)
        if (prime[i])
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;

    vector<int> primes;
    for (int i = 0; i < prime.size(); ++i)
        if (prime[i])
            primes.push_back(i);

    return {primes, prime};
}

vector<int> generate_min_divisors(int n) {
    vector<int> lp(n + 1);
    lp[1] = 1;
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
            lp[i * primes[j]] = primes[j];
    }
    return lp;
}

vector<int> primes;
vector<bool> is_prime;
vector<int> min_divisor;

void solve() {
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    bool flag = true;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "Bob" << '\n';
        return;
    }
    int mx_prime = 0;
    for (int v : arr) {
        if (is_prime[v]) {
            if (v < mx_prime) {
                cout << "Alice" << '\n';
                return;
            }
            else mx_prime = v;
        }
        else {
            if (v == 1) {
                if (v < mx_prime) {
                    cout << "Alice" << '\n';
                    return;
                }
                else mx_prime = 1;
            }
            else {
                int mn = min_divisor[v];
                while (v % mn == 0) {
                    v /= mn;
                }
                if (v > 1) { // at least 2 prime factors
                    cout << "Alice" << '\n';
                    return;
                }
                if (mn < mx_prime) { // smaller than the pre prime factors
                    cout << "Alice" << '\n';
                    return;
                }
                else mx_prime = mn;
            }
        }
    }
    cout << "Bob" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    tie(primes, is_prime) = get_primes(1000000);
    min_divisor = generate_min_divisors(1000000);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
