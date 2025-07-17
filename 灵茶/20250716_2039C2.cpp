#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 1000003;

ull n, m;

ull dfs(int pos, ull cur) {
	if (pos < 0) return cur % n == 0;
	int x = ((n >> pos) & 1), y = ((m >> pos) & 1);
	ull res = 0, l, r;
	if (y) {
		ull tmp = x ? cur + (1ull << pos) : cur;
		r = tmp + (1ull << pos) - 1;
		l = (tmp > 0 ? tmp - 1 : 0);
		res += (r / n) - (l / n);
	}
	cur = (x ^ y) ? cur + (1ull << pos) : cur;
	return res + dfs(pos - 1, cur);
}

void solve() {
	cin >> n >> m;
	int nl = bit_width(n), ml = bit_width(m);
	ull ans = 0;
	for (int i = 1; i < min(m + 1, (1ull << (nl - 1))); ++i) {
		if ((n ^ i) % i == 0) ++ans;
	}
	if (m >= n) ++ans; // 0 is the special case when the highest bit is the same as n
	if (ml <= nl) {
		cout << ans << '\n';
		return;
	}
	ans += dfs(ml - 1, 0);
	cout << ans - 1 << '\n'; // can't be the n itself because y can't be 0
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}