#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#define LL long long
using namespace std;
const int maxn = 150010;
LL a[maxn], f[1000][1000];
int main() {
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        for (int p = 1; p * p <= n; p++)
            f[p][i%p] += a[i];
    }
    char ch[2];
    while (m--) {
        scanf("%s%d%d", ch, &x, &y);
        if (ch[0] == 'A') {
            if (x * x <= n) {
                printf("%lld\n", f[x][y]);
            } else {
                LL sum = 0;
                for (int i = y; i <= n; i += x)
                    sum += a[i];
                printf("%lld\n", sum);
            }
        } else {
            for (int p = 1; p * p <= n; p++) 
                f[p][x%p] = f[p][x%p] - a[x] + y;
            a[x] = y;
        }
    }
    return 0;
}