// https://atcoder.jp/contests/abc212/tasks/abc212_d
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	multiset<ll> s;
	ll delta = 0;
	for (int i = 1, op, x; i <= n; ++i) {
		cin >> op;
		if (op == 3) {
			cout << *s.begin() + delta << '\n';
			s.erase(s.begin());
		}
		else {
			cin >> x;
			if (op == 1) {
				s.insert(x - delta);
			}
			else {
				delta += x;
			}
		}
	}
	return 0;
}