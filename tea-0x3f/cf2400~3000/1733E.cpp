// Problem: E. Conveyor
// Contest: Codeforces - Codeforces Round 821 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1733/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>

using namespace std;

void solve() {
    long long t;
    int x, y;
    cin >> t >> x >> y;

    long long K = t - x - y;
    
    if (K < 0) {
        cout << "NO\n";
        return;
    }

    // dp[i][j] 记录前 K 个史莱姆经过 (i, j) 的次数
    // 优化：只需推演到我们关心的最大坐标 (x, y) 即可
    vector<vector<long long>> dp(x + 1, vector<long long>(y + 1, 0));
    dp[0][0] = K;

    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            if (i < x) {
                dp[i + 1][j] += dp[i][j] / 2;         // 向下的分配数量
            }
            if (j < y) {
                dp[i][j + 1] += (dp[i][j] + 1) / 2;   // 向右的分配数量
            }
        }
    }

    int cx = 0, cy = 0;
    while (cx <= x && cy <= y) {
        if (cx == x && cy == y) {
            cout << "YES\n";
            return;
        }
        
        // 根据该格子被经过的次数的奇偶性，决定当前目标史莱姆的走向
        if (dp[cx][cy] % 2 == 0) {
            cy++; // 偶数次，初始状态，向右
        } else {
            cx++; // 奇数次，翻转状态，向下
        }
    }
    
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}