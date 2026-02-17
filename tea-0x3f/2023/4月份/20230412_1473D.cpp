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
	int n, m;
	cin >> n >> m;
	vi arr(n + 1);
	vi a(n + 2);
	vector<pii> pre(n + 2), suf(n + 2);
	int cur = 0;
	for (int i = 1; i <= n; ++i) {
		char c;
		cin >> c;
		arr[i] = c == '+' ? 1 : -1;
		cur += arr[i];
		a[i] = cur;
		pre[i].first = max(pre[i - 1].first, cur);
		pre[i].second = min(pre[i - 1].second, cur);
	}
	for (int i = n; i >= 1; --i) {
		suf[i].first = max(0, suf[i + 1].first + arr[i]);
		suf[i].second = min(0, suf[i + 1].second + arr[i]);
	}
	while (m--) {
		int l, r;
		cin >> l >> r;
		int pr = pre[l - 1].first, pl = pre[l - 1].second;
		int sr = suf[r + 1].first + a[l - 1], sl = suf[r + 1].second + a[l - 1];
		cout << max(pr, sr) - min(pl, sl) + 1 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}