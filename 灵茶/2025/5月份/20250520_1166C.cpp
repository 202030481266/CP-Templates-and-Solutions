// https://codeforces.com/problemset/problem/1166/C

#include <bits/stdc++.h>

using namespace std;

void cf1166C() {
	int n;
	cin >> n;
	vector<int> a;
	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		a.push_back(abs(x));
	}
	ranges::sort(a);
	int l = 0;
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		while (a[i] > 2 * a[l]) ++l;
		ans += i - l;
	}
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cf1166C();
}