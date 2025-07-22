#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;

void solve() {
	// answer is k , then means [0, k) should at lease have one element
	// n - k >= i, i is the remove times, and i >= cnt[k]
	// cnt[k] <= i <= n - k
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> cnt(n + 2);
	vector<int> sum(n + 2);
	for (int& v : a) cin >> v;
	for (int v : a) cnt[v]++;
	int ed = 0;
	while (ed <= n && cnt[ed]) ++ed;
	for (int i = 0; i <= ed; ++i) {
		int l = cnt[i], r = n - i;
		if (l <= r) {
			sum[l]++;
			sum[r + 1]--;
		}
	}
	int cur = 0;
	for (int i = 0; i <= n; ++i) {
		cur += sum[i];
		cout << cur << ' ';
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) solve();
}