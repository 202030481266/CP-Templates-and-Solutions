#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 500005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n;
int a[maxn];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	ll ans = 0;
	for (int i = 1, l1, l2; i < n - 1; ++i) {
		l1 = 0, l2 = i - 1;
		for (int j = i + 1; j < n && l1 < i; ++j) {
			while (l1 < i && a[i] + a[l1] <= a[j]) ++l1;
			while (l2 >= 0 && a[i] + a[l2] + a[j] > a[n - 1]) --l2;
			ans += i - max(l2 + 1, l1);
		}
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}