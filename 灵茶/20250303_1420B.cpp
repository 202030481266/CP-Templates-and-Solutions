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

int cnt[32];
uint arr[maxn];

void solve() {
	memset(cnt, 0, sizeof(cnt));
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) {
		if (arr[i]) ++cnt[bit_width(arr[i])];
		else ++cnt[0];
	}
	ll ans = 0;
	for (int i = 0; i < 31; ++i) {
		ans += 1ll * cnt[i] * (cnt[i] - 1) / 2;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}