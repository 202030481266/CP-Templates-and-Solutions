// https://www.luogu.com.cn/problem/P5094
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int mod = 998'244'353;
static constexpr int inf = 0x3f3f3f3f;

int n;
ll ans = 0;
array<int, 2> points[50010];
array<int, 2> tmp[50010];

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);
	int p1 = l, p2 = mid + 1, p = l;
	ll sum = 0, cur = 0;
	for (int i = l; i <= mid; ++i) sum += points[i][1];
	while (p2 <= r) {
		while (p1 <= mid && points[p1][1] <= points[p2][1]) {
			cur += points[p1++][1];
		}
		// [l, p), [p, mid + 1)
		ans += points[p2][0] * (1ll * (2 * p1 - l - mid - 1) * points[p2][1] + (sum - 2 * cur));
		p2++;
	}
	p1 = l, p2 = mid + 1;
	while (p1 <= mid && p2 <= r) {
		if (points[p1][1] <= points[p2][1]) {
			tmp[p++] = points[p1++];
		}
		else {
			tmp[p++] = points[p2++];
		}
	}
	while (p1 <= mid) tmp[p++] = points[p1++];
	while (p2 <= r) tmp[p++] = points[p2++];
	for (int i = l; i <= r; ++i) {
		points[i] = tmp[i];
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> points[i][0] >> points[i][1];
	sort(points + 1, points + 1 + n);
	cdq(1, n);
	cout << ans << '\n';
	return 0;
}

