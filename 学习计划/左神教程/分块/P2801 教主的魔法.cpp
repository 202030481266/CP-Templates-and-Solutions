#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000010;
long long n, q, a[maxn], belong[maxn], st[10010], ed[10010], delta[10010];
long long t[maxn]; // 不能改变位置

void Sort(int k) {
	for (int i = st[k]; i <= ed[k]; ++i) t[i] = a[i];
	sort(t + st[k], t + ed[k] + 1);
}

int get(int l, int r, int c) {
	int ans = 0, x = belong[l], y = belong[r];
	if (x == y) {
		for (int i = l; i <= r; ++i)
			if (a[i] + delta[x] >= c) ++ans;
		return ans;
	}
	for (int i = l; i <= ed[x]; ++i)
		if (a[i] + delta[x] >= c) ++ans;
	for (int i = r; i >= st[y]; --i)
		if (a[i] + delta[y] >= c) ++ans;
	for (int i = x + 1; i < y; ++i) {
		int tmp = lower_bound(t + st[i], t + ed[i] + 1, c - delta[i]) - t; // [tmp, ed[i]] is valid
		ans += (ed[i] - tmp + 1);
	}
	return ans;
}

void modify(int l, int r, int c) {
	int x = belong[l], y = belong[r];
	if (x == y) {
		for (int i = l; i <= r; ++i)
			a[i] += c;
		Sort(x);
		return;
	}
	for (int i = l; i <= ed[x]; ++i) 
		a[i] += c;
	for (int i = r; i >= st[y]; --i)
		a[i] += c;
	for (int i = x + 1; i < y; ++i) 
		delta[i] += c;
	Sort(x);
	Sort(y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	int num = sqrt(n);
	for (int i = 1; i <= num; ++i)
		st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
	ed[num] = n;
	for (int i = 1; i <= num; ++i) {
		for (int j = st[i]; j <= ed[i]; ++j) belong[j] = i;
	}
	for (int i = 1; i <= num; ++i) Sort(i);
	char op;
	int l, r, w;
	while (q--) {
		cin >> op >> l >> r >> w;
		if (op == 'M') {
			modify(l, r, w);
		}
		else {
			cout << get(l, r, w) << '\n';
		}
	}
}