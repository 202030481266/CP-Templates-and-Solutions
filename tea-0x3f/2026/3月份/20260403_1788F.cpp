// Problem: F. XOR, Tree, and Queries
// Contest: Codeforces - Codeforces Round 851 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1788/F
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

// guess1: 拆位来分析会比较简单
// guess2: 分析一下，就是满足条件下，要使得其中1的数量尽量是偶数
// guess3: 简单版本分析一下似乎不是很难，就是将这里的条件看成是 sr^sl = x
// sr^sl==x,如果 x>>i&1 == 1，说明 sr和sl在这个位置上是不同的，他们是不同的集合
// 无解的情况本质上就是sr和sl在某个时候得知是一样的，但是他们后来有发现是不一样的，无解
// 因此，此题做法就是 拆位置 + 并查集判断 + 树上前缀和
// 保证最小，我们可以看一看：
// 最后所有边的异或和可以等价于度数为奇数的点的前缀和的异或和，我们需要看看这些点的分布情况
// 找出所有不同的点的分布，这意味着他们必然是对立的，如果这种对立是偶数，最后结果为1，否则为0
// a如果b'一个集合，那么b肯定和a'一个集合，镜像的关系，找出一个集合中所有的这些点，除以2


int n, q;
int degree[MAXN];
int ans[MAXN];
int value[MAXN];
vp edges;
vi nodes, others;
int big[MAXN], tot[MAXN];

struct DSU
{
    vector<int> par, rnk, sz, val;
    int c;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n)
    {
        for (int i = 1; i <= n; ++i)
            par[i] = i;
    }
    void init(int n) {
        par = vi(n + 1);
        rnk = vi(n + 1);
        sz = vi(n + 1);
        c = n;
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    int find(int i)
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }
    bool same(int i, int j)
    {
        return find(i) == find(j);
    }
    int get_size(int i)
    {
        return sz[find(i)];
    }
    int count()
    {
        return c; // connected components
    }
    int merge(int i, int j)
    {
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

void solve() {
    cin >> n >> q;
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        edges.emplace_back(u, v);
        ++degree[u];
        ++degree[v];
    }
    for (int i = 1; i <= n; ++i) {
        if (degree[i] & 1) {
            nodes.push_back(i);
            nodes.push_back(i + n);
        }
        else {
            others.push_back(i);
            others.push_back(i + n);
        }
    }
    vec<tuple<int, int, int>> arr;
    for (int i = 0, u, v, x; i < q; ++i) {
        cin >> u >> v >> x;
        arr.emplace_back(u, v, x);
    }
    DSU dsu(n * 2);
    auto update = [&](int i, int v) -> void {
        int fi = dsu.find(i);
        int fr = i > n ? dsu.find(i - n) : dsu.find(i + n);
        value[fi] = v;
        value[fr] = 1 ^ v;
    };
    for (int b = 0; b < 30; ++b) {
        for (auto [u, v, x] : arr) {
            if (x >> b & 1) {
                if (dsu.same(u, v) || dsu.same(u + n, v + n)) {
                    cout << "No" << '\n';
                    return;
                }
                dsu.merge(u, v + n);
                dsu.merge(u + n, v);
            }
            else {
                if (dsu.same(u + n, v) || dsu.same(v + n, u)) {
                    cout << "No" << '\n';
                    return;
                }
                dsu.merge(u, v);
                dsu.merge(u + n, v + n);
            }
        }
        memset(value, -1, (n * 2 + 1) * sizeof(int));
        memset(big, 0, (2 * n + 1) * sizeof(int));
        memset(tot, 0, (2 * n + 1) * sizeof(int));
        for (int i : nodes) {
            int fa = dsu.find(i);
            ++tot[fa];
            if (i > n) ++big[fa];
        }
        int odd = 0, tmp = -1, flag = 0;
        for (int i : nodes) {
            int fa = dsu.find(i);
            if (value[fa] != -1) continue;
            if (tot[fa] & 1) {
                tmp = fa;
                flag = big[fa] & 1;
            }
            else if (big[fa] & 1) {
                ++odd;
                update(fa, 1);
            }
        }
        if ((odd & 1) && tmp != -1) update(tmp, flag ^ 1);
        for (int i : nodes) {
            int fa = dsu.find(i);
            if (value[fa] != -1) continue;
            if (big[fa] & 1) update(fa, 1);
            else update(fa, 0);
        }
        for (int i : others) {
            int fa = dsu.find(i);
            if (value[fa] != -1) continue;
            update(fa, 0);
        }
        for (int i = 0; i < n - 1; ++i) {
            ans[i] ^= (value[dsu.find(edges[i].first)] ^ value[dsu.find(edges[i].second)]) << b;
        }
        dsu.init(2 * n);
    }
    cout << "Yes" << '\n';
    for (int i = 0; i < n - 1; ++i) cout << ans[i] << ' ';
    // int sum = 0;
    // for (int i = 0; i < n - 1; ++i) sum ^= ans[i];
    // debug(sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}