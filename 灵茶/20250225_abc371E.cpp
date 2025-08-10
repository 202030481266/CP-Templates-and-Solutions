#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> pre(n + 1);
	ll res = 0, ans = 0;
	for (int i = 1, v; i <= n; ++i) {
		cin >> v;
		int l = pre[v]; // (l, i)
		res += 1ll * (i - l - 1) * (i - l) / 2;
		pre[v] = i;
	}
	for (int i = 1; i <= n; ++i) {
		if (pre[i]) {
			ans += 1ll * n * (n + 1) / 2;
			res += 1ll * (n + 1 - pre[i] - 1) * (n + 1 - pre[i]) / 2;
		}
	}
	cout << ans - res << endl;
}