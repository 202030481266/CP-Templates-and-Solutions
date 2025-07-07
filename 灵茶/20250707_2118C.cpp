#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
ll k;

ll lowbit(ll x) {
	return x & -x;
}

void solve() {
	cin >> n >> k;
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
	int ans = 0;
	for (int i = 1, v; i <= n; ++i) {
		cin >> v;
		ans += __builtin_popcount(v);
		q.emplace(lowbit(v + 1), v);
	}
	while (!q.empty()) {
		auto [cost, v] = q.top();
		if (cost > k) break;
		++ans;
		k -= cost;
		q.pop();
		v = (v + 1) | v;
		q.emplace(lowbit(v + 1), v);
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}