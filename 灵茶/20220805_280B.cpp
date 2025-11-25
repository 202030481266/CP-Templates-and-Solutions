#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

int n, arr[MAXN];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	vector<unordered_map<int, int>> pos(30);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (i > 1 && arr[i - 1] < arr[i]) {
			int p = i - 1, left = 0;
			for (int x = 29; x >= 0; --x) {
				int cur = arr[p] >> x, b = arr[i] >> x & 1, c = cur & 1;
				if (!c && !b) {
					++cur;
					if (pos[x].count(cur) && pos[x][cur] > left && arr[pos[x][cur]] < arr[i]) p = pos[x][cur];
				}
				else if (!c) {
					++cur;
					if (pos[x].count(cur)) left = max(left, pos[x][cur]);
				}
			}
			ans = max(ans, arr[i] ^ arr[p]);
		}
		for (int x = 29; x >= 0; --x) pos[x][arr[i] >> x] = i;
	}
	for (int i = 0; i < 30; ++i) pos[i].clear();
	for (int i = n; i >= 1; --i) {
		if (i < n && arr[i + 1] < arr[i]) {
			int p = i + 1, right = n + 1;
			for (int x = 29; x >= 0; --x) {
				int cur = arr[p] >> x, b = arr[i] >> x & 1, c = cur & 1;
				if (!c && !b) {
					++cur;
					if (pos[x].count(cur) && pos[x][cur] < right && arr[pos[x][cur]] < arr[i]) p = pos[x][cur];
				}
				else if (!c) {
					++cur;
					if (pos[x].count(cur)) right = min(right, pos[x][cur]);
				}
			}
			ans = max(ans, arr[i] ^ arr[p]);
		}
		for (int x = 29; x >= 0; --x) pos[x][arr[i] >> x] = i;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t = 1;
	while (t--)
		solve();
}
