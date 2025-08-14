#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5010;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n, k;
ll arr[50], sum[1 << 13], sumr[1 << 13], fac[20], S;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k >> S;
	for (int i = 0; i < n; ++i) cin >> arr[i];
	int m = n / 2, N = n - m;
	fac[0] = 1;
	for (int i = 1; i <= 18; ++i) fac[i] = fac[i - 1] * i;
	for (int i = 1; i < (1 << m); ++i) {
		for (int j = 0; j < m; ++j) {
			if ((i >> j) & 1) sum[i] += arr[j];
		}
	}
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < N; ++j) {
			if ((i >> j) & 1) sumr[i] += arr[m + j];
		}
	}
	map<ll, int> cnt[30];
	for (int i = 0; i < (1 << m); ++i) {
		ll tmp = S, cur = 0, flag = 1;
		int x = __builtin_popcount(i);
		if (x > k) continue;
		for (int j = 0; j < m; ++j) {
			if ((i >> j) & 1) {
				if (arr[j] > 18 || tmp < fac[arr[j]]) {
					flag = 0;
					break;
				}
				tmp -= fac[arr[j]];
				cur += fac[arr[j]];
			}
		}
		if (flag) {
			for (int j = i; j < (1 << m); j = (j + 1) | i) {
				cnt[x][cur + sum[j ^ i]]++;
			}
		}
	}
	for (int i = 1; i <= k; ++i) {
		for (auto const& [val, num] : cnt[i - 1]) {
			cnt[i][val] += num;
		}
	}
	ll ans = 0;
	for (int i = 0; i < (1 << N); ++i) {
		ll tmp = S, cur = 0;
		int x = __builtin_popcount(i), flag = 1;
		if (x > k) continue;
		for (int j = 0; j < N; ++j) {
			if ((i >> j) & 1) {
				if (arr[m + j] > 18 || tmp < fac[arr[m + j]]) {
					flag = 0;
					break;
				}
				tmp -= fac[arr[m + j]];
				cur += fac[arr[m + j]];
			}
		}
		if (flag) {
			for (int j = i; j < (1 << N); j = (j + 1) | i) {
				tmp = cur + sumr[j ^ i];
				if (tmp <= S) {
					ans += cnt[k - x][S - tmp];
				}
			}
		}
	}
	cout << ans << '\n';
}