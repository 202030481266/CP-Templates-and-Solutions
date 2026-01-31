// https://www.luogu.com.cn/problem/P1903


// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_1903.cpp
# Author: xiaoshulin
# Created Time: 2021/12/7 15:01:48
#########################################################################*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 240000, inf = 0x3f3f3f3f;
int n, m, val[maxn], ans[maxn], cnt[2000000];
struct query {int l, r, id, tim;} q[maxn];
struct change {int pos, color, last;} c[maxn];
int sum = 0, buck_num, siz, totq, totc, belong[maxn];

inline int cmp(query a, query b) {
	return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] :
		((belong[a.r] ^ belong[b.r]) ? belong[a.r] < belong[b.r] : a.tim < b.tim);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> val[i];
	for(int i = 1; i <= m; i++) {
		char op; int x, y;
		cin >> op >> x >> y;
		if(op == 'Q') {
			q[++totq].l = x;
			q[totq].r = y;
			q[totq].id = totq;
			q[totq].tim = totc;
		} else {
			c[++totc].pos = x;
			c[totc].color = y;
			c[totc].last = val[x];
		}
	}
	siz = pow(n, (2.0)/(3.0)); // 注意这里的块的长度
	buck_num = ceil((double)n / siz);
	for(int i = 1; i <= buck_num; i++) 
		for(int j = (i - 1) * siz + 1; j <= i * siz; j++) 
			belong[j] = i;
	sort(q + 1, q + 1 + totq, cmp);
	int l = 1, r = 0, t = 0, now = 0;
	for(int i = 1; i <= totq; i++) {
		int ql = q[i].l, qr = q[i].r, tim = q[i].tim;
		while(l < ql) now -= !--cnt[val[l++]];
		while(l > ql) now += !cnt[val[--l]]++;
		while(r < qr) now += !cnt[val[++r]]++;
		while(r > qr) now -= !--cnt[val[r--]];
		while(t < tim) {
			t++;
			if(ql <= c[t].pos && qr >= c[t].pos) now -= !--cnt[val[c[t].pos]] - !cnt[c[t].color]++;
			swap(val[c[t].pos], c[t].color);
		}
		while(t > tim) {
			if(ql <= c[t].pos && qr >= c[t].pos) now -= !--cnt[val[c[t].pos]] - !cnt[c[t].color]++;
			swap(val[c[t].pos], c[t].color);
			t--;
		}
		ans[q[i].id] = now;
	}
	for(int i = 1; i <= totq; i++) {
		cout << ans[i] << endl;
	}
}