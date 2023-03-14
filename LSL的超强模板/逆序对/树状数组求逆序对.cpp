#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
typedef long long LL;
LL c[maxn], n, ans, rk[maxn];
struct edge {int x; LL y;} e[maxn];
bool cmp (edge A, edge B) {
	if (A.y == B.y) return A.x < B.x;
	else return A.y < B.y;
}
int lowbit(int x) {return (-x) & x;}
void add(int i) {
	while (i <= n) {
		c[i]++;
		i += lowbit(i);
	}
}
LL sum(int i) {
	LL s = 0;
	while (i > 0) {
		s += c[i];
		i -= lowbit(i);
	}
	return s;
}
int main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%lld", &e[i].y), e[i].x = i;
	sort(e+1, e+n+1, cmp);
	for (int i = 1; i <= n; i++) {
		add(e[i].x);
		ans += i - (sum(e[i].x));
	}
	cout << ans << endl;
	return 0;
}