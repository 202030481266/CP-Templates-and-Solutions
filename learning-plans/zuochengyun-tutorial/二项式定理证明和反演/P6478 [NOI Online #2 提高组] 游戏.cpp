// 树上背包 + 二项式反演

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 5001;
const int MOD = 998244353;

int n, m;
int arr[MAXN];
long long fac[MAXN];
long long c[MAXN][MAXN];
int head[MAXN], nextEdge[MAXN << 1], to[MAXN << 1], cnt;
int subtreeSize[MAXN]; // 重命名为 subtreeSize
int belong[MAXN][2];
long long dp[MAXN][MAXN];
long long backup[MAXN];
long long g[MAXN];
long long f[MAXN];

void build() {
    cnt = 1;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        fac[i] = fac[i - 1] * i % MOD;
    }
    for (int i = 0; i <= n; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}

void addEdge(int u, int v) {
    nextEdge[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int u, int fa) {
    subtreeSize[u] = 1; // 使用 subtreeSize 替代 size
    belong[u][0] = belong[u][1] = 0;
    belong[u][arr[u]] = 1;
    dp[u][0] = 1;
    // For all children of u
    for (int e = head[u]; e; e = nextEdge[e]) {
        int v = to[e];
        if (v != fa) {
            dfs(v, u);
            // Copy dp[u][i] to backup[i] and reset dp[u][i]
            int limit_u = min(subtreeSize[u] / 2, m); // 使用 subtreeSize
            for (int i = 0; i <= limit_u; i++) {
                backup[i] = dp[u][i];
                dp[u][i] = 0;
            }
            int limit_v = min(subtreeSize[v] / 2, m); // 使用 subtreeSize
            for (int l = 0; l <= limit_u; l++) {
                for (int r = 0; r <= min(limit_v, m - l); r++) {
                    dp[u][l + r] = (dp[u][l + r] + backup[l] * dp[v][r] % MOD) % MOD;
                }
            }
            subtreeSize[u] += subtreeSize[v]; // 使用 subtreeSize
            belong[u][0] += belong[v][0];
            belong[u][1] += belong[v][1];
        }
    }
    // Update dp[u][i]
    int num = belong[u][arr[u] ^ 1];
    int limit_num = min(num, m);
    for (int i = 1; i <= limit_num; i++) {
        backup[i] = dp[u][i];
    }
    for (int i = 1; i <= limit_num; i++) {
        dp[u][i] = (dp[u][i] + backup[i - 1] * (num - i + 1) % MOD) % MOD;
    }
}

void compute() {
    dfs(1, 0);
    for (int i = 0; i <= m; i++) {
        g[i] = dp[1][i] * fac[m - i] % MOD;
    }
    for (int k = 0; k <= m; k++) {
        f[k] = 0;
        for (int i = k; i <= m; i++) {
            if (((i - k) & 1) == 0) {
                f[k] = (f[k] + c[i][k] * g[i] % MOD) % MOD;
            } else {
                f[k] = (f[k] + (MOD - c[i][k]) * g[i] % MOD) % MOD;
            }
        }
    }
}

int main() {
    // Input reading
    scanf("%d", &n);
    m = n / 2;
    build();
    string str;
    cin >> str;
    for (int i = 1; i <= n; i++) {
        arr[i] = str[i - 1] - '0';
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    compute();
    for (int k = 0; k <= m; k++) {
        printf("%lld\n", f[k]);
    }
    return 0;
}
