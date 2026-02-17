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
	int n, k;
	cin >> n >> k;
	set<int> pos;
	set<pii> s;
	vi arr(n);
	vi valid(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
		s.emplace(arr[i], i);
		pos.insert(i);
	}
	int step = 1;
	while (!pos.empty()) {
		auto [_, p] = *s.rbegin();
		s.erase(prev(s.end()));
		if (!valid[p]) {
			auto it = pos.lower_bound(p);
			valid[p] = step & 1 ? 1 : 2;
			for (int i = 0; i < k && next(it) != pos.end(); ++i) {
				valid[*next(it)] = step & 1 ? 1 : 2;
				pos.erase(next(it));
			}
			for (int i = 0; i < k && it != pos.begin(); ++i) {
				valid[*prev(it)] = step & 1 ? 1 : 2;
				pos.erase(prev(it));
			}
			pos.erase(it);
			++step;
		}
	}
	for (int v : valid) cout << v;
	cout << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
	return 0;
}