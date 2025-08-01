#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& v : a) cin >> v;
	vector<int> sum;
	sum.push_back(0);
	for (int v : a) sum.push_back(sum.back() ^ v);
	if (sum.back() == 0) {
		cout << -1 << '\n';
		return 0;
	}
	vector<int> xbase(32);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 30; j >= 0; --j) {
			if ((sum[i] >> j) & 1) {
				if (xbase[j]) {
					sum[i] ^= xbase[j];
				}
				else {
					xbase[j] = sum[i];
					++ans;
					break;
				}
			}
		}
	}
	cout << ans << endl;
}