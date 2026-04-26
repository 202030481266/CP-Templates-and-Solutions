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

// 注意 a[i]<=1000，那么最后的gcd肯定也是小于等于1000
// 枚举所有数字最后能够除以 x 所需要的最少的操作次数，因为 x 的因子个数最多是 840，只有32个, 而且不同的质因数最多就是4个

vpp factors(1001);

void precompute() {
	for (int i = 2; i <= 1000; ++i) {
		int temp = i;
		for (int j = 2; j * j <= temp; ++j) {
			if (temp % j == 0) {
				int cnt = 0;
				while (temp % j == 0) {
					++cnt;
					temp /= j;
				}
				factors[i].emplace_back(j, cnt);
			}
		}
		if (temp > 1) {
			factors[i].emplace_back(temp, 1);
		}
	}
}

constexpr int MAX_LIMIT = 1000;
constexpr int MAX_POWER = 15;

int pw[MAX_LIMIT + 5][MAX_POWER];

void generatePrimePowers() {
	vector<bool> is_prime(MAX_LIMIT + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (int p = 2; p * p <= MAX_LIMIT; p++) {
		if (is_prime[p]) {
			for (int i = p * p; i <= MAX_LIMIT; i += p) {
				is_prime[i] = false;
			}
		}
	}
	for (int p = 2; p <= MAX_LIMIT; p++) {
		if (is_prime[p]) {
			long long current_val = p;
			int k = 1;
			pw[p][0] = 1;
			while (current_val <= MAX_LIMIT) {
				pw[p][k] = current_val;
				current_val *= p;
				k++;
			}
		}
	}
}

void dfs(ll current, const vector<int>& primes, int prime_idx, vector<int>& result) {
	result.push_back(current);
	for (int i = prime_idx; i < primes.size(); ++i) {
		if (current * primes[i] <= 1000) {
			dfs(current * primes[i], primes, i, result);
		}
	}
}

vector<int> generateNumbers(const vector<int>& primes) {
	vector<int> result;
	dfs(1, primes, 0, result);
	sort(result.begin(), result.end());
	return result;
}

int dp[100001][1001];

void solve() {
	int n, k;
	if (!(cin >> n >> k)) return;
	vi arr(n + 1);
	int g = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		g = gcd(g, arr[i]);
	}
	vii tree(n + 1);
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	int ans = arr[1];
	if (g == 1) {
		cout << arr[1] << '\n';
		return;
	}

	vi primes;
	for (auto [p, _] : factors[g]) {
		primes.push_back(p);
	}
	int m = primes.size();

	for (int i = 1; i <= n; ++i) {
		int& v = arr[i];
		int x = v;
		v = 1;
		for (int f : primes) {
			while (x % f == 0) {
				v *= f;
				x /= f;
			}
		}
	}

	auto tmp = generateNumbers(primes);
	vi b;
	for (int v : tmp) {
		if (v * g <= 1000) b.push_back(v * g);
	}
	int b_sz = b.size();

	vector<int> b_idx(1005, -1);
	for (int i = 0; i < b_sz; ++i) {
		b_idx[b[i]] = i;
	}

	vector<vector<int>> dp(n + 1, vector<int>(b_sz, INF));

	static int P[1005][4];
	memset(P, 0, sizeof(P));
	for (int x = 1; x <= 1000; ++x) {
		for (int i = 0; i < m; ++i) {
			int temp = x;
			while (temp % primes[i] == 0) {
				P[x][i]++;
				temp /= primes[i];
			}
		}
	}

	vector<vector<int>> trans_idx(b_sz, vector<int>(b_sz, -1));
	for (int i = 0; i < b_sz; ++i) {
		for (int j = 0; j < b_sz; ++j) {
			int num = b[i], val = b[j];
			long long t = 1;
			bool valid = true;
			for (int k = 0; k < m; ++k) {
				int req = max(P[num][k], P[val][k] - P[num][k]);
				t *= pw[primes[k]][req];
				if (t > 1000) { valid = false; break; }
			}
			if (valid && t <= 1000 && b_idx[t] != -1) {
				trans_idx[i][j] = b_idx[t];
			}
		}
	}

	auto cal = [&](auto&& self, int u, int fa) -> void {
		for (int v : tree[u]) {
			if (v != fa) self(self, v, u);
		}

		int sum_dp[35];
		for (int j = 0; j < b_sz; ++j) {
			int cur_sum = 0;
			for (int v : tree[u]) {
				if (v != fa) {
					if (dp[v][j] == INF) {
						cur_sum = INF;
						break;
					}
					cur_sum += dp[v][j];
				}
			}
			sum_dp[j] = cur_sum;
		}

		for (int j = 0; j < b_sz; ++j) {
			int val = b[j];
			int t = 1;
			bool cannot = false;
			for (int i = 0; i < m; ++i) {
				int n1 = P[arr[u]][i];
				int n2 = P[val][i];
				if (n1 < n2) {
					if (n2 > n1 * 2) {
						cannot = true;
						break;
					}
					t *= pw[primes[i]][n2 - n1];
				}
			}
			if (cannot) continue;

			if (t == 1) {
				if (sum_dp[j] != INF) {
					dp[u][j] = sum_dp[j];
				}
			}

			if (u > 1) {
				for (int i = 0; i < b_sz; ++i) {
					int num = b[i];
					if (num < t || num % t != 0) continue;
					if (num > arr[u] || num > val) break;

					int c_idx = trans_idx[i][j];
					if (c_idx != -1 && sum_dp[c_idx] != INF) {
						dp[u][j] = min(dp[u][j], sum_dp[c_idx] + 1);
					}
				}
			}
		}
	};

	cal(cal, 1, 0);

	int mx = 1;
	for (int j = 0; j < b_sz; ++j) {
		if (dp[1][j] <= k - 1) mx = max(mx, b[j]);
	}
	cout << ans * mx << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	precompute();
	generatePrimePowers();
	int t = 1;
	cin >> t;
	while (t--) solve();
}