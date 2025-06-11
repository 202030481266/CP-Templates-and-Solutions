// https://codeforces.com/problemset/problem/2061/C
#define GCC
#ifdef GCC
#include <bits/stdc++.h>
#endif
#ifdef WIN
#include "stdafx.h" // use stdafx.h to accelerate
#endif

using namespace std;
using ll = long long;

static constexpr int mod = 998'244'353;
static constexpr int inf = 0x3f3f3f3f;


static void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int x = 1, y = 1;
	if (a[0] == 0) b[0] = 1;
	for (int i = 1; i < n; ++i) {
		int nx = a[i - 1] + 1, ny = b[i - 1];
		if (a[i - 1] == a[i]) b[i] = (b[i] + b[i - 1]) % mod;
		if (a[i] == x) b[i] = (b[i] + y) % mod;
		x = nx;
		y = ny;
	}
	cout << (y + b[n - 1]) % mod << '\n';
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}