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
	vl a1(n), a2(n), b1(n), b2(n);
	vi vis(n);
	priority_queue<pair<ll, int>> q;
	ll sum = 0;
	for (int i = 0; i < n; ++i) {
		cin >> a1[i] >> b1[i] >> a2[i] >> b2[i];
		if (a1[i] + b1[i] >= a2[i] + b2[i]) {
			q.emplace(a1[i] + b1[i], i);
		}
		else {
			if (b1[i] - a2[i] >= 0 && b2[i] - a1[i] >= 0) sum -= b1[i] - a2[i];
			if (a1[i] - b2[i] >= 0 && a2[i] - b1[i] >= 0) sum += a1[i] - b2[i];
		}
	}
	ll A = 0, B = 0;
	int flag = 0;
	while (!q.empty()) {
		auto [val, idx] = q.top();
		q.pop();
		if (!flag) {
			if (!vis[idx]) {
				A += a1[idx];
				vis[idx] = 1;
				q.emplace(a2[idx] + b2[idx], idx);
			}
			else A += a2[idx];
		}
		else {
			if (!vis[idx]) {
				B += b1[idx];
				vis[idx] = 1;
				q.emplace(a2[idx] + b2[idx], idx);
			}
			else B += b2[idx];
		}
		flag ^= 1;
	}
	cout << A - B + sum << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
}