#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 50005;
int n, k, fa[maxn], d[maxn];
void init() {
    for (int i = 1; i <= 50005; i++) {
        fa[i] = i;
        d[i] = 0;
    }
}
int find(int x) {
    int fx = fa[x];
    if (x != fa[x]) {
        fa[x] = find(fa[x]);
        d[x] = (d[x] + d[fx]) % 3;
    }
    return fa[x];
}
int main() {
	init();
    cin >> n >> k; int ans = 0;
    while (k--) {
        int a, b, c;
        scanf("%d%d%d", &c, &a, &b);
        if (a > n || b > n || (c == 2 && a == b))
            ans++;
        else {
            int x = find(a), y = find(b);
            if (x == y) {
                if ((d[a] - d[b] + 3) % 3 != c - 1)
                    ans++;
            } else {
                fa[x] = y;
                d[x] = (d[b] - d[a] + c - 1 + 3) % 3;
            }
        }
    }
    cout << ans << endl;
    return 0;
}