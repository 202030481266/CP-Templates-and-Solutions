// https://codeforces.com/problemset/problem/1045/G
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int mod = 998'244'353;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 100010;

int N, K;
int b[maxn * 3], m;
ll ans = 0;
array<int, 3> a[maxn];
array<int, 3> tmp[maxn];

int get(int val) {
	return lower_bound(b + 1, b + m + 1, val) - b;
}

ll fenwick[maxn * 3];

int lowbit(int i) {
	return i & -i;
}

void add(int x, ll val) {
	for (; x <= m; x += lowbit(x)) fenwick[x] += val;
}

ll query(int x) {
	ll res = 0;
	for (; x; x -= lowbit(x)) res += fenwick[x];
	return res;
}

void cdq(int l, int r) {
	if (l == r) return;
	int mid = (l + r) / 2;
	cdq(l, mid);
	cdq(mid + 1, r);
	int p1 = l, p3 = l, p2 = mid + 1, p = l;
	while (p2 <= r) {
		while (p1 <= mid && a[p1][2] <= a[p2][2] + K) {
			add(get(a[p1][0]), 1);
			++p1;
		}
		while (p3 <= mid && a[p3][2] < a[p2][2] - K) {
			add(get(a[p3][0]), -1);
			++p3;
		}
		ans += query(get(a[p2][0] + a[p2][1])) - query(get(a[p2][0] - a[p2][1] - 1));
		p2++;
	}
	while (p3 < p1) {
		add(get(a[p3++][0]), -1);
	}
	p1 = l, p2 = mid + 1;
	while (p1 <= mid && p2 <= r) {
		if (a[p1][2] <= a[p2][2]) tmp[p++] = a[p1++];
		else tmp[p++] = a[p2++];
	}
	while (p1 <= mid) tmp[p++] = a[p1++];
	while (p2 <= r) tmp[p++] = a[p2++];
	for (int i = l; i <= r; ++i) a[i] = tmp[i];
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		cin >> a[i][0] >> a[i][1] >> a[i][2];
	}
	for (int i = 1; i <= N; ++i) {
		// (a[i][0] - a[i][1] - 1, a[i][0] + a[i][1]]
		b[++m] = a[i][0];
		b[++m] = a[i][0] + a[i][1];
		b[++m] = a[i][0] - a[i][1] - 1;
	}
	sort(b + 1, b + m + 1);
	m = unique(b + 1, b + m + 1) - b - 1;
	sort(a + 1, a + N + 1, [&](const auto& x, const auto& y) {
		return x[1] > y[1];
		});
	cdq(1, N);
	cout << ans << '\n';
}