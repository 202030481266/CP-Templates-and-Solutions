#include <bits/stdc++.h>
using namespace std;
const int maxn = 30010;
int fa[maxn], d[maxn], cnt[maxn], n;
int find(int x) {
	int fx = fa[x];
	if (x != fa[x]) {
		fa[x] = find(fa[x]);
		d[x] += d[fx];
	}
	return fa[x];
}
int join(int x, int y) {
	int a = find(x), b = find(y);
	fa[a] = b;
	d[a] += cnt[b];
	cnt[b] += cnt[a];
}
int main() {
	char ch[0]; int x, y;
	for (int i = 1; i <= maxn; i++) {
		fa[i] = i;
		d[i] = 0;
		cnt[i] = 1;
	}
	cin >> n;
	while (n--) {
		scanf("%s%d%d", ch, &x, &y);
		if (ch[0] == 'M') {
			join(x, y);
		} else {
			if (find(x) == find(y)) {
	
				printf("%d\n", abs(d[x] - d[y]) - 1);
			} else puts("-1");
		}
	}
	return 0;
}