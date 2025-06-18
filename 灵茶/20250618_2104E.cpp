// https://codeforces.com/problemset/problem/2104/E
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int n, m, q;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	vector<char> s(n);
	vector<int> need(n, 0);
	vector<int> cost(m, 0);
	int mn = 0, cnt = m;
	for (int i = 0; i < n; ++i) cin >> s[i];
	for (int i = n - 1, c; i >= 0; --i) {
		need[i] = mn + 1;
		c = s[i] - 'a';
		if (cost[c] == mn) {
			cost[c] = need[i];
			--cnt;
			if (cnt == 0) {
				++mn;
				cnt = m;
			}
		}
	}
	cin >> q;
	vector<string> matches(q);
	for (int i = 0; i < q; ++i) {
		cin >> matches[i];
	}
	vector pos(m, vector<int>());
	vector<int> ptr(q);
	vector<int> ed(q);
	for (int i = 0; i < q; ++i) {
		pos[matches[i][0] - 'a'].push_back(i);
	}
	for (int i = 0, c; i < n; ++i) {
		c = s[i] - 'a';
		vector<int> update;
		for (int& j : pos[c]) {
			update.push_back(j);
		}
		pos[c].clear();
		for (int& j : update) {
			++ptr[j];
			ed[j] = i;
			if (ptr[j] < (int)matches[j].size()) {
				pos[matches[j][ptr[j]] - 'a'].push_back(j);
			}
		}
	}
	for (int i = 0; i < q; ++i) {
		if (ptr[i] != (int)matches[i].size()) {
			cout << 0 << '\n';
		}
		else {
			cout << need[ed[i]] << '\n';
		}
	}
}