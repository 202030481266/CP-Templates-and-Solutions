// https://codeforces.com/problemset/problem/645/D
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector g(n, vector<int>());
	vector<array<int, 2>> edges(m);
	for (auto& e : edges) {
		cin >> e[0] >> e[1];
		e[0]--;
		e[1]--;
	}
	vector<int> cnt(n);
	int c_zero = n, p = 0;
	while (p < m && c_zero > 1) {
		int u = edges[p][0], v = edges[p][1];
		g[u].push_back(v);
		++cnt[v];
		if (cnt[v] == 1) c_zero--;
		++p;
	}
	if (c_zero > 1) {
		cout << -1 << '\n';
		return 0;
	}
	int start = 0, num = 0;
	for (int i = 0; i < n; ++i) {
		if (cnt[i] == 0) {
			start = i;
			break;
		}
	}
	vector<int> care(n, 0);
	vector<int> used(n, 0);
	int s_used = 0;
	for (int v : g[start]) {
		if (cnt[v] == 1) {
			care[v] = 1;
			++num;
		}
	}
	int timestamp = 1;
	while (s_used < n) {
		while (num > 1 && p < m) {
			int u = edges[p][0], v = edges[p][1];
			if (!used[u]) {
				++cnt[v];
				g[u].push_back(v);
				if (care[v] == timestamp) {
					--num;
					care[v] = 0;
				}
			}
			++p;
		}
		if (num > 1) {
			std::cout << -1 << '\n';
			return 0;
		}
		used[start] = 1;
		++s_used;
		for (int v : g[start]) {
			--cnt[v];
			if (cnt[v] == 0) {
				start = v;
			}
		}
		num = 0;
		++timestamp;
		for (int v : g[start]) {
			if (cnt[v] == 1) {
				care[v] = timestamp;
				++num;
			}
		}
	}
	std::cout << p << '\n';
}