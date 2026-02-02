#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;


void solve() {
	int n, k;
	cin >> n >> k;
	vi sum(n + 1);
	ll tot = 1ll * n * (n + 1) / 2;
	for (int i = 1; i <= n; ++i) {
		cin >> sum[i];
		sum[i] ^= sum[i - 1];
	}
	ranges::sort(sum);
	// a ^ b = (1<<k) - 1, means a bigger, b smaller, a + b = (1<<k) - 1
	vector<pii> arr;
	int p = 0;
	n = sum.size();
	while (p < n) {
		int i = p + 1;
		while (i < n && sum[i] == sum[p]) ++i;
		arr.emplace_back(sum[p], i - p);
		p = i;
	}
	auto cal = [&](int x, int y) -> void {
		int mid = (x + y) / 2, rem = x + y - mid;
		tot -= 1ll * mid * (mid - 1) / 2 + 1ll * rem * (rem - 1) / 2;
	};
	int m = arr.size();
	for (int i = 0; i < m; ++i) {
		auto it = lower_bound(arr.begin(), arr.end(), make_pair((1 << k) - 1 ^ arr[i].first, 0));
		if (it == arr.end()) {
			cal(arr[i].second, 0);
		}
		else {
			int j = it - arr.begin();
			if ((arr[j].first ^ arr[i].first) == (1 << k) - 1) {
				if (j > i) cal(arr[i].second, arr[j].second);
			}
			else cal(arr[i].second, 0);
		}
	}
	cout << tot << '\n';
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}