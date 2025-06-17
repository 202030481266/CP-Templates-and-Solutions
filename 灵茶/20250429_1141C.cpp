// https://codeforces.com/problemset/problem/1141/C
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
int n, m;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<ll> a(n);
	ll mn = 0;
	for (int i = 1; i < n; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
		if (a[i] < mn) {
			mn = a[i];
		}
	}
	ll sub = 1 - mn;
	vector<int> exi(n + 1);
	for (int i = 0; i < n; ++i) {
		a[i] += sub;
		if (a[i] > n || exi[a[i]]) {
			cout << -1 << endl;
			return 0;
		}
		exi[a[i]] = 1;
	}
	for (int i = 0; i < n; ++i) {
		cout << a[i] << (i != n - 1 ? ' ' : '\n');
	}
}