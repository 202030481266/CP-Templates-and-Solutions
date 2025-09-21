// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_3709.cpp
# Author: xiaoshulin
# Created Time: 2021/12/7 21:18:46
#########################################################################*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7, inf = 0x3f3f3f3f;
int n, m, val[maxn], aa[maxn], cnt[maxn], ans[maxn];
int t[maxn], l = 1, r, Ans, siz, buck_num, belong[maxn];
struct query {int l, r, id;} q[maxn];

inline int cmp(query a, query b) {
	return (belong[a.l] ^ belong[b.l]) ? (belong[a.l] < belong[b.l]) : 
		((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
inline void add(int pos) {
	t[cnt[val[pos]]]--;
	t[++cnt[val[pos]]]++;
	Ans = max(Ans, cnt[val[pos]]);
}
inline void del(int pos) {
	t[cnt[val[pos]]]--;
	if(cnt[val[pos]] == Ans && !t[cnt[val[pos]]]) Ans--;
	t[--cnt[val[pos]]]++;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m; 
	siz = sqrt(n);
	for(int i = 1; i <= n; i++) cin >> val[i], aa[i] = val[i], belong[i] = (i - 1) / siz + 1;
	sort(aa + 1, aa + 1 + n);
	int len = unique(aa + 1, aa + 1 + n) - aa - 1;
	for(int i = 1; i <= n; i++) 
		val[i] = lower_bound(aa + 1, aa + 1 + len, val[i]) - aa;
	//buck_num = ceil((double) n / siz);
	for(int i = 1; i <= m; i++) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	sort(q + 1, 1 + q + m, cmp);
	for(int i = 1; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while(l < ql) del(l++);
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(r > qr) del(r--);
		ans[q[i].id] = Ans;
	}
	for(int i = 1; i <= m; i++) cout << -ans[i] << endl;
}