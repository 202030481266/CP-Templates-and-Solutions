#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int a[maxn], b[maxn];

void solve() {
	int n, d, k;
	cin >> n >> d >> k;
	vector<pii> jobs(k);
	for (int i = 0; i < k; ++i) {
		cin >> jobs[i].first >> jobs[i].second;
		a[jobs[i].first] += 1;
		b[jobs[i].second + 1] -= 1;
	}
	int l = 1, sum = 0;
	int mx = -1, mn = inf;
	int x = -1, y = -1;
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
		while (i - l + 1 >= d) sum += b[l++];
		if (i >= d) {
			if (sum > mx) {
				mx = sum;
				x = i - d + 1;
			}
			if (sum < mn) {
				mn = sum;
				y = i - d + 1;
			}
		}
	}
	for (int i = 0; i < k; ++i) {
		a[jobs[i].first] = 0;
		b[jobs[i].second + 1] = 0;
	}
	cout << x << ' ' << y << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}