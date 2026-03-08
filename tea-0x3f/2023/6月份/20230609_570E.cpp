// Problem: E. Pig and Palindromes
// Contest: Codeforces - Codeforces Round 316 (Div. 2)
// URL: https://codeforces.com/problemset/problem/570/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

// 核心的观察在于使用步数优化所有了一个维度，使其空间占用小了一个维度，不然非常easy

const int MOD = 1e9 + 7;

int f[505][505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    if (a[0][0] != a[n-1][m-1]) {
        cout << 0;
        return 0;
    }
    
    // f[r1][r2], r2 ranges up to n+1
    // reset
    memset(f, 0, sizeof(f));
    f[1][n] = 1;
    
    for (int i = 1; i < (n + m) / 2; i++) {
        // iterate in reverse to avoid overwriting (we read f[r1][r2+1] and f[r1-1][...])
        // but since we write f[r1][r2] based on previous i, we need a temp copy
        // Actually in the Go code, f is updated in-place each step i
        // We need a new array each iteration
        vector<vector<int>> nf(n + 2, vector<int>(n + 2, 0));
        
        for (int r1 = min(n, i + 1); r1 >= 1 && r1 >= i + 2 - m; r1--) {
            int c1 = i + 2 - r1;
            for (int r2 = max(1, n - i); r2 <= n && r2 < n + m - i; r2++) {
                int c2 = n + m - i - r2;
                if (a[r1-1][c1-1] == a[r2-1][c2-1]) {
                    nf[r1][r2] = (((f[r1][r2] + f[r1][r2+1]) % MOD
                                  + f[r1-1][r2+1]) % MOD
                                  + f[r1-1][r2]) % MOD;
                } else {
                    nf[r1][r2] = 0;
                }
            }
        }
        
        for (int x = 0; x <= n + 1; x++)
            for (int y = 0; y <= n + 1; y++)
                f[x][y] = nf[x][y];
    }
    
    long long ans = 0;
    if ((n + m) % 2 != 0) {
        for (int i = 1; i <= n; i++)
            ans += f[i][i] + f[i][i+1];
    } else {
        for (int i = 1; i <= n; i++)
            ans += f[i][i];
    }
    
    cout << ans % MOD;
    return 0;
}