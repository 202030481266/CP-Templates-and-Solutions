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
	string s;
	cin >> s;
	vi cnt(26);
	for (char c : s) cnt[c - 'a']++;
	int t = 0;
	vi arr;
	for (int i = 0; i < 26; ++i) {
		if (cnt[i] > 0) arr.push_back(i);
	}
	int n = arr.size();
	if (n == 1) {
		cout << s << '\n';
		return;
	}
	vii g(2);
	for (int i = 0; i < n; ++i) {
		g[i & 1].push_back(arr[i]);
	}
	if (g[0].back() - g[1][0] > 1) {
		for (int v : g[0]) {
			while (cnt[v]--) cout << (char)(v + 'a');
		}
		for (int v : g[1]) {
			while (cnt[v]--) cout << (char)(v + 'a');
		}
		cout << '\n';
	}
	else if (g[1].back() - g[0][0] > 1) {
		for (int v : g[1]) {
			while (cnt[v]--) cout << (char)(v + 'a');
		}
		for (int v : g[0]) {
			while (cnt[v]--) cout << (char)(v + 'a');
		}
		cout << '\n';
	}
	else cout << "No answer\n";
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
}