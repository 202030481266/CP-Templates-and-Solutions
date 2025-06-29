#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 100005;
static constexpr int maxb = 320;

int n, m, c, lastans = 0;
int arr[maxn], bl[maxn], br[maxn], b[maxn];
int fre[maxb][maxn], even[maxb][maxb], cnt[maxn];

int change(int val) {
	if (val == 1) return 0;
	return (val & 1) ? -1 : 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> c >> m;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	int blen = (int)sqrt(n);
	int bnum = (n + blen - 1) / blen;
	for (int i = 1; i <= n; ++i) b[i] = (i - 1) / blen + 1;
	for (int i = 1; i <= bnum; ++i) {
		bl[i] = (i - 1) * blen + 1;
		br[i] = min(n, i * blen);
	}
	for (int i = 1; i <= bnum; ++i) {
		for (int j = 1; j <= c; ++j) fre[i][j] = fre[i - 1][j];
		for (int j = bl[i]; j <= br[i]; ++j) fre[i][arr[j]]++;
	}
	for (int i = 1; i <= bnum; ++i) {
		for (int j = i; j <= bnum; ++j) {
			even[i][j] = even[i][j - 1];
			for (int k = bl[j]; k <= br[j]; ++k) {
				cnt[arr[k]]++;
				even[i][j] += change(cnt[arr[k]] + fre[j - 1][arr[k]] - fre[i - 1][arr[k]]);
			}
			for (int k = bl[j]; k <= br[j]; ++k) cnt[arr[k]] = 0;
		}
	}
	for (int t = 1, l, r; t <= m; ++t) {
		cin >> l >> r;
		l = ((l + lastans) % n) + 1;
		r = ((r + lastans) % n) + 1;
		if (r < l) swap(l, r);
		lastans = 0;
		if (b[l] == b[r]) {
			for (int i = l; i <= r; ++i) {
				++cnt[arr[i]];
				lastans += change(cnt[arr[i]]);
			}
			for (int i = l; i <= r; ++i) cnt[arr[i]] = 0;
		}
		else {
			lastans = even[b[l] + 1][b[r] - 1];
			for (int i = l; i <= br[b[l]]; ++i) {
				cnt[arr[i]]++;
				lastans += change(cnt[arr[i]] + fre[b[r]-1][arr[i]] - fre[b[l]][arr[i]]);
			}
			for (int i = bl[b[r]]; i <= r; ++i) {
				cnt[arr[i]]++;
				lastans += change(cnt[arr[i]] + fre[b[r]-1][arr[i]] - fre[b[l]][arr[i]]);
			}
			for (int i = l; i <= br[b[l]]; ++i) cnt[arr[i]] = 0;
			for (int i = bl[b[r]]; i <= r; ++i) cnt[arr[i]] = 0;
		}
		cout << lastans << '\n';
	}
}