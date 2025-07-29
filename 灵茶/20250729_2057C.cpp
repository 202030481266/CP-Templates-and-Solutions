#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int l, r;

void solve() {
	cin >> l >> r;
	int a = 0, p = 30;
	while (p >= 0) {
		int x = ((l >> p) & 1), y = ((r >> p) & 1);
		if (x ^ y) break;
		a |= (x << p);
		--p;
	}
	a |= (1 << p);
	int b = a - 1, c;
	if (a == r) c = b - 1;
	else c = a + 1;
	// cout << a << ' ' << b << ' ' << c << '\n';
	cout << (a ^ b) + (b ^ c) + (c ^ a) << endl;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}