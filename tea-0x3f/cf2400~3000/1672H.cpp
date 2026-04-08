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

inline constexpr int  MAXN = 200'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;


// guess1: 1s的时间，说明存在非常高效的方法解决，甚至不带log
// guess2: 建模为一个01block的模型，比方说 0001101101 -> [3,2,1,2,1,1]
// guess3: 0相当于往下走（因为0如果要匹配后面的1，必须前面的0消除掉），1相当于往上走（匹配前面的0，那么前面的0肯定要消除掉）
// guess3: 感觉还是栈的关系，这个计数有点巧妙了，如何快速统计是一个难题，应该是和波峰有关系

int arr[MAXN];
int belong[MAXN], bl[MAXN], br[MAXN];

void solve() {
	int n, m;
	cin >> n >> m;
	string data;
	cin >> data;
	for (int i = 1; i <= n; ++i) arr[i] = data[i - 1] - '0';
	int p = 1, num = 0;
	vi block;
	vi sum{ 0 };
	while (p <= n) {
		int i = p + 1;
		while (i <= n && arr[i] == arr[p]) ++i;
		++num;
		for (int j = p; j < i; ++j) belong[j] = num;
		bl[num] = p;	
		br[num] = i - 1;
		block.push_back(i - p);
		sum.push_back(sum.back() + i - p);
		p = i;
	}
	for (int t = 0, l, r; t < m; ++t) {
		cin >> l >> r;
		if (belong[l] == belong[r]) cout << r - l + 1 << '\n';
		else {
			int left_num = br[belong[l]] - l + 1;
			int right_num = r - bl[belong[r]] + 1;
			if (belong[r] == belong[l] + 1) {
				cout << (right_num > left_num ? right_num : left_num) << '\n';
			}
			else {
			}
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}