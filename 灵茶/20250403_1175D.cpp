#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int maxn = 300005;

ll sum[maxn];
int n, k;


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> k;
	priority_queue<ll> q;
	for (int i = 0; i < n; ++i) cin >> sum[i];
	for (int i = n - 1; i >= 0; --i) {
		sum[i] += sum[i + 1];
		if (i > 0)
			q.emplace(sum[i]);
	}
	ll ans = sum[0];
	k--;
	while (k--) {
		ans += q.top();
		q.pop();
	}
	cout << ans << '\n';
}
