// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_5355.cpp
# Author: xiaoshulin
# Created Time: 2021/12/9 18:02:37
#########################################################################*/
#include <bits/stdc++.h> 
using namespace std;
const int maxn = 100010, N = 1e5;
bitset<maxn> s1, s2;
int n, m, val[maxn], belong[maxn], cnt[maxn], ans[maxn];

struct Query {
	int opt, l, r, id, v;
	inline bool operator < (const Query& x) const {
		if(belong[l] != belong[x.l]) return l < x.l;
		else return (belong[l] & 1) ? r < x.r : r > x.r;
	}
} q[maxn];
struct Specialquery {
	int l, r, id;
};
inline void add(int x) {
	x = val[x];
	if(!(cnt[x]++)) s1[x] = s2[N - x] = true;
}
inline void del(int x) {
	x = val[x];
	if(!(--cnt[x])) s1[x] = s2[N - x] = false;
}
int coapr[maxn], apr[maxn]; 
vector<Specialquery> sp[maxn];
inline void special(int siz) {
	for(int x = 1; x <= siz; x++) {
		if(sp[x].empty()) continue;
		memset(coapr, 0, sizeof(coapr));
		memset(apr, 0, sizeof(apr));
		int now = 0;
		for(int i = 0; i <= n; i++) {
			int w = val[i];
			apr[w] = i;
			if(w * x <= N) {
				now = max(now, apr[w * x]);
			}
			if(!(w % x)) {
				now = max(now, apr[w / x]);
			}
			coapr[i] = now;
		}
		for(auto p : sp[x]) {
			ans[p.id] = (p.l <= coapr[p.r]);
		}
	}
}
int main() {
	cin >> n >> m;
	int limit = 500, _cnt = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
	for(int i = 1; i <= m; i++) {
		int opt, l, r, v;
		scanf("%d%d%d%d", &opt, &l, &r, &v);
		if(opt == 4 && v <= limit && v) {
			sp[v].push_back(Specialquery{l, r, i});
			continue;
		}
		q[++_cnt].opt = opt;
		q[_cnt].l = l;
		q[_cnt].r = r;
		q[_cnt].v = v;
		q[_cnt].id = i;
	}
	for(int i = 1, siz = sqrt(n); i <= n; i++) belong[i] = i / siz;
	sort(q + 1, 1 + q + _cnt);
	int l = 1, r = 0;
	for(int i = 1; i <= _cnt; i++) {
		int ql = q[i].l, qr = q[i].r; 
		//cout << q[i].id << endl;
		while(l < ql) del(l++);
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(r > qr) del(r--);
		int op = q[i].opt, x = q[i].v;
		if(op == 1) {
			ans[q[i].id] = (s1 & (s1 << x)).any();
		} else if(op == 2) {
			ans[q[i].id] = (s1 & (s2 >> (N - x))).any();
		} else if(op == 3) {
			if(x == 0) {
				ans[q[i].id] = s1[0];
			} else {
				for(int j = 1; (j * j) <= x; j++) {
					if(!(x % j)) {
						if(s1[j] & s1[x / j]) {
							ans[q[i].id] = true;
							break;
						}
					}
				}
			}
		} else {
			if(x == 0) {
				if(ql != qr) ans[q[i].id] = s1[0]; 
			} else {
				for(int j = 1; j * x <= n; j++) {
					if(s1[j] & s1[j * x]) {
						ans[q[i].id] = true;
						break;
					}
				}
			}
		}
	}
	special(limit);
	for(int i = 1; i <= m; i++)
		cout << (ans[i] ? "yuno" : "yumi") << endl;
}