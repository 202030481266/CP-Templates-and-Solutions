// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_2709.cpp
# Author: xiaoshulin
# Created Time: 2021/12/7 20:58:46
#########################################################################*/
#include <bits/stdc++.h> 
using namespace std;
const int maxn = 5e5 + 7, inf = 0x3f3f3f3f;
int n, m, k, val[maxn], ans[maxn], cnt[maxn];
int siz, buck_num, now, l = 1, r, belong[maxn]; 
struct query {int l, r, id;} q[maxn];

inline int cmp(query a, query b) {
	return (belong[a.l] ^ belong[b.l]) ? (belong[a.l] < belong[b.l]) :
		((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
inline void add(int pos) {
	now += (cnt[val[pos]] * 2 + 1);
	cnt[val[pos]]++;
}
inline void del(int pos) {
	cnt[val[pos]]--;
	now -= (cnt[val[pos]] * 2 + 1);
}
int main() {
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) cin >> val[i];
	for(int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	siz = sqrt(n);
	buck_num = ceil((double) n / siz);
	for(int i = 1; i <= buck_num; i++)
		for(int j = (i - 1) * siz + 1; j <= i * siz; j++)
			belong[j] = i;
	sort(q + 1, q + 1 + m, cmp);
	for(int i = 1; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while(l < ql) del(l++);
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(r > qr) del(r--);
		ans[q[i].id] = now;
	}
	for(int i = 1; i <= m; i++)
		cout << ans[i] << endl;
}