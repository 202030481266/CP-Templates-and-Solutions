// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_3521.cpp
# Author: xiaoshulin
# Created Time: 2021/12/12 14:47:00
#########################################################################*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7, mxr = maxn;
int n, cnt = 0; 
ll ans, pre, aft;

#define mid ((l + r) >> 1)
#define maxm maxn * 60
int sl[maxm], sr[maxm], siz[maxm];

void modify(int& x, int l, int r, int pos) {
	if(x == 0) x = ++cnt, siz[x]++;
	if(l == r) return;
	if(pos <= mid) modify(sl[x], l, mid, pos);
	else modify(sr[x], mid + 1, r, pos);
}
int merge(int a, int b, int l, int r) {
	if(a == 0 || b == 0) return a + b;
	if(l == r) {
		siz[a] += siz[b];
		return a;
	}
	pre += (ll)siz[sr[a]] * siz[sl[b]];
	aft += (ll)siz[sl[a]] * siz[sr[b]];
	sl[a] = merge(sl[a], sl[b], l, mid);
	sr[a] = merge(sr[a], sr[b], mid + 1, r);
	siz[a] = siz[sl[a]] + siz[sr[a]];
	return a;
}
int dfs() {
	int pos = 0, val;
	cin >> val;
	if(val == 0) {
		int ls, rs;
		ls = dfs();
		rs = dfs();
		pre = aft = 0;
		pos = merge(ls, rs, 1, n);
		ans += min(pre, aft);
	} else modify(pos, 1, n, val);
	return pos;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	dfs();
	cout << ans << endl;
}