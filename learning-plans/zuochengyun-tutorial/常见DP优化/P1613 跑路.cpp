// 其实只要理解了ST表的构造就不难
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 100;
const int inf = 0x3f3f3f3f3f3f3f3f;

int f[maxn][maxn], n, m;
int g[maxn][maxn][70];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(f, 0x3f, sizeof(f));
    memset(g, false, sizeof(g));

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        f[x][y] = 1; // Oriented graph
        g[x][y][0] = true;
    }

    for (int k = 1; k <= 70; k++) {
        for (int i = 1; i <= n; i++) {
            for (int t = 1; t <= n; t++) {
                for (int j = 1; j <= n; j++) {
                    if (g[i][t][k-1] && g[t][j][k-1]) {
                        g[i][j][k] = true;
                        f[i][j] = 1;
                    }
                }
            }
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    cout << f[1][n] << endl;
    return 0;
}
