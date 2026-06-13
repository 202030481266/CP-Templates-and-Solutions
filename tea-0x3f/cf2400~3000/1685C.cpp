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

    n <<= 1;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        if (c == '(') s[i] = 1;
        else s[i] = -1;
    }

    // we should eliminate the negative brackets in our edeavour.
    // everytime we just do the same things -> swap the open brackets before the closed brackets

    vi sum(n + 1);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + s[i];

    vi f(n + 1);
    vp ans;
    int last = 0;
    while (last < n) {
        // sum[p] < 0
        int pos = last + 1;
        while (pos <= n && sum[pos] >= 0) ++pos;
        if (pos > n) break;
        int q = last;
        int mx = 0;
        for (int i = last + 1; i < pos; ++i) {
            if (sum[i] >= mx) {
                mx = sum[i];
                q = i;
            }
        }
        int p = q + 1;
        f[q] = 0;
        for (int i = q + 1; i <= n; ++i) {
            f[i] = min(f[i - 1] + s[i], s[i]);
            if (f[i] + sum[q] >= 0) p = i;
        }
        int l = q + 1, r = p;
        ans.emplace_back(l, r);
        while (l < r) {
            swap(s[l], s[r]);
            ++l;
            --r;
        }
        last = p;
    }

    cout << ans.size() << '\n';
    for (auto [l, r] : ans) cout << l << ' ' << r << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

