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

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

void solve() {
	int n;
	cin >> n;
	vi arr(n);
	for (int i = 0; i < n; ++i) {
		char c;
		cin >> c;
		arr[i] = c - '0';
	}
	vector<pii> st(n + 3);
	int ptr = 0;
	ll sum = 0, ans = 0;
	int p = 0;
	while (p < n) {
		int i = p + 1;
		while (i < n && arr[i] == arr[p]) ++i;
		// i - p, i - p + 1, ... 3, 2, 1
		if (arr[p]) {
			for (int j = p; j < i; ++j) {
				while (ptr > 0 && st[ptr - 1].first <= j - p + 1) {
					auto [val, ed] = st[ptr - 1];
					--ptr;
					int last = ptr ? st[ptr - 1].second : -1;
					sum -= 1LL * (ed - last) * val;
				}
				sum += ptr ? 1LL * (j - p + 1) * (p - st[ptr - 1].second) : 1LL * (j - p + 1) * (p + 1);
				st[ptr++] = { j - p + 1, p };
				// 1 2 3 4... j - p
				ans += sum;
				if (j > p) ans += 1LL * (j - p + 1) * (j - p) / 2;
			}
			for (int j = p + 1; j < i; ++j) {
				st[ptr++] = { i - j, j };
				sum += i - j;
			}
		}
		else {
			ans += sum * (i - p);
			st[ptr++] = { 0, i - 1 };
		}
		p = i;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
	return 0;
}