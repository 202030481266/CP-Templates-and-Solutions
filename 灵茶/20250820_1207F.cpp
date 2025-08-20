#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 500005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;
static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };


ll f[710][710], a[maxn];

static constexpr int n = 500000;
static constexpr int m = 707;

int main() {
	int q, op, x, y;
	cin >> q;
	while (q--) {
		scanf("%d %d %d", &op, &x, &y);
		if (op == 1) {
			for (int p = 1; p <= m; ++p) {
				f[p][x % p] += y;
			}
			a[x] += y;
		}
		else {
			if (x <= m) {
				printf("%lld\n", f[x][y]);
			}
			else {
				ll res = 0;
				for (int i = (y == 0 ? x : y); i <= n; i += x) {
					res += a[i];
				}
				printf("%lld\n", res);
			}
		}
	}
}