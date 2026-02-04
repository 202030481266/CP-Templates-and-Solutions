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

static constexpr int MAXN = 2e5 + 7;
static constexpr int MOD = 998244353;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
	int n, m;
	cin >> n >> m;
	vi a(n), b(m);
	for (int& v : a) cin >> v;
	for (int& v : b) cin >> v;
	ranges::sort(a);
	ranges::sort(b);
	ll sa = accumulate(a.begin(), a.end(), 0ll);
	ll sb = accumulate(b.begin(), b.end(), 0ll);
	if (sa != sb) {
		cout << "No\n";
		return;
	}
	multiset<int> s;
	for (int v : b) s.insert(v);
	int i = n - 1;
	while (i >= 0 && (int)s.size() <= i + 1) {
		if (s.empty()) {
			cout << "No\n";
			return;
		}
		if (a[i] > *s.rbegin()) {
			cout << "No\n";
			return;
		}
		else if (a[i] == *s.rbegin()) {
			s.erase(prev(s.end()));
			--i;
		}
		else {
			int val = *s.rbegin();
			s.erase(prev(s.end())); // most split n - m times
			s.insert(val / 2);
			s.insert(val - val / 2);
		}
	}
	if (i < 0 && s.empty()) cout << "Yes\n";
	else cout << "No\n";
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
}

