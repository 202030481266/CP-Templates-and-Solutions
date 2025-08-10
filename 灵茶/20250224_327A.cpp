#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	// (r - l) - (sum[r] - sum[l]) - (sum[r] - sum[l])
	// r - l - 2 * sum[r] + 2 * sum[l] = r - 2 * sum[r] + 2 * sum[l] - l
	int mx = 0, sum = 0, delta = -inf;
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
		delta = max(delta, i - 2 * sum + mx);
		mx = max(mx, 2 * sum - i);
	}
	cout << sum + delta << endl;
}