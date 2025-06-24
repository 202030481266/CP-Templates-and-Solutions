// https://codeforces.com/problemset/problem/2117/C
#include <bits/stdc++.h>
using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		vector<int> nxt(n);
		vector<int> pos(n+1, n);
		for (int& v : a) cin >> v;
		for (int i = n - 1; i >= 0; --i) {
			nxt[i] = pos[a[i]];
			pos[a[i]] = i;
		}
		int i = 0, ed = nxt[0], ans = 0;
		while (i < n) {
			while (i < n && nxt[i] <= ed) ++i;
			++ans;
			if (ed == n) break;
			int tmp = ed;
			for (int j = i; j <= tmp; ++j) {
				ed = max(ed, nxt[j]);
			}
		}
		cout << ans << '\n';
	}
}