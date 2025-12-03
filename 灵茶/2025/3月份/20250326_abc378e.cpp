#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 200005;

int n, mod;
ll sum[maxn];

inline int lowbit(int i) {
	return i & -i;
}

int fenwick[maxn];

void update(int p, int val) {
	while (p <= mod) {
		fenwick[p] += val;
		p += lowbit(p);
	}
}

int query(int p) {
	int res = 0;
	while (p > 0) {
		res += fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> mod;
	for (int i = 1; i <= n; ++i) {
		cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	int l = 0;
	ll cur = 0, ans = 0, pre = 0;
	for (int i = 1; i <= n; ++i) {
		while (sum[i] - sum[l] >= mod) {
			update(sum[l] % mod + 1, 1);
			cur -= sum[l];
			pre += sum[l] % mod;
			++l;
		}
		// (l, i]
		ans += sum[i] * (i - l) - cur;
		// [0, l)
		ans += (sum[i] % mod) * l - pre + (l - query(sum[i] % mod + 1)) * mod;
		cur += sum[i];
	}
	cout << ans << endl;
}
