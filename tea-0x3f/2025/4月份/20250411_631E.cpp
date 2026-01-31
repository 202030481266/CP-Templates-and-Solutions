#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;

int n, nxt[maxn], ed;
pii q[maxn];
ll arr[maxn];
ll sum[maxn], ans = 0;

bool cmp1(int p, int q, int l) {
	ll vp = sum[p] - sum[l] - arr[p] * (p - l);
	ll vq = sum[q] - sum[l] - arr[q] * (q - l);
	return vp > vq;
}

ll solve1() {
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
	int p = n;
	for (int i = n; i >= 1; --i) {
		nxt[i] = p;
		if (arr[i] < arr[p]) p = i;
	}
	ed = 0;
	int r = nxt[1];
	q[ed++] = { r, 0 };
	while (r < n) {
		r = nxt[r];
		while (ed > 0) {
			int l = q[ed - 1].second, pr = q[ed - 1].first;
			if (cmp1(r, pr, l)) --ed;
			else break;
		}
		if (ed == 0) q[ed++] = { r, 0 };
		else {
			int vl = q[ed - 1].second, vr = q[ed - 1].first;
			int pr = vr;
			while (vl + 1 < vr) {
				int mid = (vl + vr) / 2;
				if (cmp1(r, pr, mid)) vr = mid;
				else vl = mid;
			}
			q[ed++] = { r, vr };
		}
	}
	p = 0;
	ll delta = 0;
	for (int i = 1; i <= n; ++i) {
		while (p < ed && q[p].second < i) ++p;
		int r = q[p - 1].first;
		delta = max(delta, sum[r] - sum[i - 1] - arr[r] * (r - i + 1));
	}
	return ans + max(0ll, delta);
}

bool cmp2(int p, int q, int l) {
	ll v1 = (p - l) * arr[p] - (sum[p] - sum[l]);
	ll v2 = (q - l) * arr[q] - (sum[q] - sum[l]);
	return v1 > v2;
}

ll solve2() {
	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + arr[i];
	ed = 0;
	int r = 1;
	q[ed++] = { 1, 0 };
	while (r < n) {
		++r;
		while (ed > 0) {
			int l = q[ed - 1].second, pr = q[ed - 1].first;
			if (cmp2(r, pr, l)) --ed;
			else break;
		}
		if (ed == 0) q[ed++] = { r, 0 };
		else {
			int vl = q[ed - 1].second, vr = q[ed - 1].first;
			int pr = vr;
			while (vl + 1 < vr) {
				int mid = (vl + vr) / 2;
				if (cmp2(r, pr, mid)) vr = mid;
				else vl = mid;
			}
			q[ed++] = { r, vr };
		}
	}
	int p = 0;
	ll delta = 0;
	for (int i = 1; i <= n; ++i) {
		while (p < ed && q[p].second < i) ++p;
		int r = q[p - 1].first;
		delta = max(delta, arr[r] * (r - i + 1) - (sum[r] - sum[i - 1]));
	}
	return ans + max(0ll, delta);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) ans += i * arr[i];
	ll res1 = solve1();
	reverse(arr + 1, arr + n + 1);
	ll res2 = solve2();
	cout << max(res1, res2) << endl;
}
