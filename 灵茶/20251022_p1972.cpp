// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_1972.cpp
# Author: xiaoshulin
# Created Time: 2021/12/7 9:49:52
#########################################################################*/
#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e6 + 7, inf = 0x3f3f3f3f;
int n, m, f[maxn], g[maxn], val[maxn];
struct query {
	int l, r, id, ret;
	bool operator < (const query& a) const {
		if(r != a.r) return r < a.r;
		else return l < a.l;
	}
} que[maxn], ans[maxn];
int c[maxn];
inline int lowbit(int x) {return x & -x;}
void add(int x, int k) {
	while(x <= n) {
		c[x] += k;
		x += lowbit(x);
	}
}
int getsum(int x) {
	int ans = 0;
	while(x >= 1) {
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
	}
	cin >> m;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d", &que[i].l, &que[i].r);
		ans[i].l = que[i].l, ans[i].r = que[i].r;
		ans[i].id = que[i].id = i;
	}
	sort(que + 1, que + 1 + m);
	int flag = 1;
	for(int i = 1; i <= m; i++) {
		int l = que[i].l, r = que[i].r;
		for(int j = flag; j <= r; j++) {
			if(f[val[j]] > 0) add(f[val[j]], -1);
			add(j, 1);
			f[val[j]] = j;
		}
		flag = r + 1;
		ans[que[i].id].ret = getsum(r) - getsum(l - 1);
	}
	for(int i = 1; i <= m; i++) {
		printf("%d\n", ans[i].ret);
	}
}