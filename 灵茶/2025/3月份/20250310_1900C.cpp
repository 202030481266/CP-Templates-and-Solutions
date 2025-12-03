#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


void solve() {
	int n;
	cin >> n;
	vector<char> s(n + 1);
	vector<int> L(n + 1), R(n + 1);
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int i = 1; i <= n; ++i) cin >> L[i] >> R[i];
	auto dfs = [&](auto&& self, int u) -> int {
		if (u == 0) return inf;
		if (L[u] == 0 && R[u] == 0) return 0;
		if (s[u] == 'L') return min(self(self, L[u]), self(self, R[u]) + 1);
		else if (s[u] == 'R') return min(self(self, L[u]) + 1, self(self, R[u]));
		return min(self(self, L[u]), self(self, R[u])) + 1;
	};
	cout << dfs(dfs, 1) << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}