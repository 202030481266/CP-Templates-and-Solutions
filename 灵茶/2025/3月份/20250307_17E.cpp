#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 2000005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 51123987;

int n, N;
char s[maxn], ss[maxn * 2 + 10];

int d[maxn * 2 + 10];
int cnt[maxn];
ll sum[maxn];
ll tot[maxn];

void manacher() {
	for (int i = 0, c = 0, r = 0; i < N; ++i) {
		int len = (i < r ? min(r - i, d[2 * c - i]) : 1);
		while (i - len >= 0 && i + len < N && ss[i - len] == ss[i + len]) ++len;
		d[i] = len;
		if (i + len > r) {
			r = i + len;
			c = i;
		}
	}
}

int main() {
	scanf("%d",&n);
	scanf("%s", s);
	N = 2 * n + 1;
	for (int i = 0; i < n; ++i) cin >> s[i];
	for (int i = 0; i < N; ++i) ss[i] = '#';
	for (int i = 0; i < n; ++i) ss[2 * i + 1] = s[i];
	manacher();
	for (int i = 0; i < N; ++i) {
		int rd = d[i] - 1, ed = (i + d[i]) / 2;
		if (rd > 0) {
			// [ed - rd, ed) is the real palindrome string
			int len = (rd + 1) / 2;
			// [ed - len, ed)
			cnt[ed - len]++;
			cnt[ed]--;
		}
	}
	for (int i = 1; i < n; ++i) {
		cnt[i] += cnt[i - 1];
	}
	sum[0] = cnt[0];
	for (int i = 1; i < n; ++i) {
		sum[i] = (sum[i - 1] + cnt[i]) % mod;
	}
	tot[0] = sum[0];
	for (int i = 1; i < n; ++i) {
		tot[i] = (tot[i - 1] + sum[i]) % mod;
	}
	ll ans = 0, res = 0;
	for (int i = 0; i < N; ++i) {
		int rd = d[i] - 1, ed = (i + d[i]) / 2;
		if (rd > 0) {
			// [ed - rd, ed) is the real palindrome string
			// [ed - rd, ed - (rd + 1) / 2] is the left interval
			// sum[ed - rd - 1] + sum[ed - rd] + sum[ed - rd + 1] + ... + sum[ed - (rd + 1) / 2 - 1]
			int len = (rd + 1) / 2;
			res += len;
			if (rd % 2 == 0) ++len;
			if (ed - len - 1 >= 0) ans = (ans + tot[ed - len - 1]) % mod;
			if (ed - rd - 2 >= 0) ans = ((ans - tot[ed - rd - 2]) % mod + mod) % mod;
		}
	}
	res = ((res - 1) % mod) * (res % mod) % mod * 25561994 % mod;
	cout << ((res - ans) % mod + mod) % mod << endl;
}