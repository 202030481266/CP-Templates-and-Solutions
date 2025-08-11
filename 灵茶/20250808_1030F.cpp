#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n, a[maxn], w[maxn], q;

ll f[3][maxn]; // w的和， i*wi 的和, ai*wi 的和

inline int lowbit(int i) {
	return i & -i;
}

void update(int p, ll val) {
	ll x = p;
	while (p <= n) {
		f[0][p] += val;
		f[1][p] = (f[1][p] + x * val % mod) % mod;
		f[2][p] = (f[2][p] + a[x] * val % mod) % mod;
		p += lowbit(p);
	}
}

ll query(int p, int dim, bool mo) { // query prefix sum
	ll res = 0;
	while (p) {
		if (mo) res = (res + f[dim][p]) % mod;
		else res += f[dim][p];
		p -= lowbit(p);
	}
	return res;
}

int lower(ll val) {
	int pos = 0, mask = 1;
	ll acc = 0;
	while ((mask << 1) <= n) mask <<= 1;
	for (int k = mask; k; k >>= 1) {
		if (pos + k <= n && acc + f[0][pos + k] < val) { // pos + k 的 lowbit 恰好就是 k
			acc += f[0][pos + k];
			pos += k;
		}
	}
	return pos + 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
		update(i, w[i]);
	}
	for (int i = 1, x, y; i <= q; ++i) {
		cin >> x >> y;
		if (x < 0) {
			x = -x;
			ll delta = y - w[x]; // change w
			update(x, delta);
			w[x] = y;
		}
		else {
			if (x == y) { // special judge
				cout << 0 << '\n';
				continue;
			}
			ll pre = query(x - 1, 0, 0), sum = query(y, 0, 0) - query(x - 1, 0, 0);
			ll val = (sum + 2 * pre + 1) / 2; // 向上取整
			int p = lower(val), offset = p - x; // [0, p - x]
			// start + offset = a[p]
			ll st = a[p] - offset; // [x, p] [p + 1, y]
			ll left1 = ((query(p, 0, 1) - query(x - 1, 0, 1)) % mod + mod) % mod;
			ll left2 = ((((query(p, 1, 1) - query(x - 1, 1, 1)) % mod + mod) % mod - left1 * x % mod) % mod + mod) % mod;
			ll left3 = ((query(p, 2, 1) - query(x - 1, 2, 1)) % mod + mod) % mod;
			ll right1 = ((query(y, 0, 1) - query(p, 0, 1)) % mod + mod) % mod;
			ll right2 = ((((query(y, 1, 1) - query(p, 1, 1)) % mod + mod) % mod - right1 * x % mod) % mod + mod) % mod;
			ll right3 = ((query(y, 2, 1) - query(p, 2, 1)) % mod + mod) % mod;
			ll res = st * (left1 - right1) % mod + (left2 - right2) % mod + (right3 - left3) % mod;
			cout << (res % mod + mod) % mod << '\n';
		}
	}
}