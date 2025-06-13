// https://codeforces.com/problemset/problem/1006/C

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 2e5 + 7;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<int> a(n);
	for (int& v : a) {
		cin >> v;
	}
	int l = 0, r = n - 1;
	long long lsum = a[0], rsum = a[n-1];
	long long ans = 0;
	while (l < r) {
		while (l < r && lsum != rsum) {
			if (lsum < rsum) {
				lsum += a[++l];
			}
			else {
				rsum += a[--r];
			}
		}
		if (l >= r) break;
		else {
			ans = lsum;
			lsum += a[++l];
		}
	}
	cout << ans << '\n';
}