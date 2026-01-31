// https://codeforces.com/problemset/problem/1989/B
#include <bits/stdc++.h>
using namespace std;

string s, t;
int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin >> T;
	while (T--) {
		cin >> s >> t;
		n = s.size();
		m = t.size();
		int res = 0;
		for (int i = 0; i < m; ++i) {
			int x = i;
			for (int j = 0; j < n; ++j) {
				if (s[j] == t[x]) {
					++x;
				}
			}
			res = max(res, x - i);
		}
		cout << n + m - res << '\n';
	}
}
