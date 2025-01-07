#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 感觉不是很难的一道题目, O(k^2*n)

int p[10][100001], flag[10];

void init(int k) {
    if (flag[k]) return;
    flag[k]  = 1;
    p[k][0] = 1 % k;
    for (int i = 1; i < 100001; ++i) {
        // 10^x % mod = 10^(x-1) * 10 % mod = 10^(x-1) % mod * 10 % mod
        p[k][i] = p[k][i-1] * 10 % k;
    }
}


class Solution {
public:
    string largestPalindrome(int n, int k) {
        init(k);
        int m = (n-1) / 2 + 1, dp[m][k], nxt[m][k];
        memset(dp, -1, sizeof(dp));
        memset(nxt, -1, sizeof(nxt));

        // n bits number, 10^x + 10^(n-1-x)        
        // init the first position

        for (int i = 0; i <= 9; ++i) {
            int r = (n-m != m-1 ? i * (p[k][n-m] + p[k][m-1]) : i * p[k][m-1]) % k;
            dp[m-1][r] = i;
        }

        // 动态规划 + 字典序
        for (int i = m-2; i >= 0; --i) {
            for (int j = 0; j <= 9; ++j) {
                for (int x = 0; x < k; ++x) {
                    if (dp[i+1][x] != -1) {
                        int r = (n-1 != 2*i ? x + j * (p[k][n-1-i] + p[k][i]) : x + j * p[k][i]) % k;
                        // 最为关键的是遍历顺序
                        dp[i][r] = j;
                        nxt[i][r] = x;
                    }
                }
            }
        }
        if (dp[0][0] == -1 || dp[0][0] == 0) return string(n,'0');

        // 构造回文串
        int cur = 0;
        string ans;
        for (int i = 0; i < m; ++i) {
            ans += char(dp[i][cur] + '0');
            cur = nxt[i][cur];
        }
        int st = (n & 1 ? m-2 : m-1);
        for (int i = st; i >= 0; --i) ans.push_back(ans[i]);

        return ans;
    }
};