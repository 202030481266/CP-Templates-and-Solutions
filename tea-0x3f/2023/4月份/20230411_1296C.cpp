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

const int offset = (1 << 20);
ll phash(int x, int y) {
	return 1LL * (x + offset) << 30 | (y + offset);
}
void solve() {
	int n;
	cin >> n;
	vector<char> ops(n);
	for (char& c : ops) cin >> c;
	vector<pair<ll, int>> trace;
	int x = 0, y = 0;
	trace.emplace_back(phash(x, y), 0);
	for (int i = 0; i < n; ++i) {
		if (ops[i] == 'U') ++y;
		else if (ops[i] == 'D') --y;
		else if (ops[i] == 'L') --x;
		else ++x;
		trace.emplace_back(phash(x, y), i + 1);
	}
	ranges::sort(trace);
	int ans = INF, l = -1, r = -1;
	int p = 0;
	n = trace.size();
	while (p < n) {
		int i = p + 1;
		while (i < n && trace[i].first == trace[p].first) ++i;
		for (int j = p + 1; j < i; ++j) {
			int step = trace[j].second - trace[j - 1].second;
			if (step < ans) {
				ans = step;
				l = trace[j - 1].second + 1;
				r = trace[j].second;
			}
		}
		p = i;
	}
	if (ans == INF) cout << -1 << '\n';
	else cout << l << ' ' << r << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}