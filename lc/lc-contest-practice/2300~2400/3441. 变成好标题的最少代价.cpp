#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    string minCostGoodCaption(string s) {
        int n = s.size(), dp[n][26][4];
        pii pre[n][26][4];
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < 26; ++i) {
            dp[n-1][i][1] = abs(i-(s[n-1]-'a'));
        }
        for (int i = n-2; i >= 0; --i) {
            int num = s[i] - 'a'; 
            for (int j = 0, cost; j < 26; ++j) {
                cost = abs(num-j);
                // 开始新的一组
                for (int x = 0; x < 26; ++x) {
                    if (x != j) {
                        if (dp[i+1][x][3] + cost < dp[i][j][1]) {
                            dp[i][j][1] = dp[i+1][x][3] + cost;
                            pre[i][j][1] = {x, 3};
                        }
                    }
                }
                // 连接
                for (int k = 2; k <= 3; ++k) {
                    if (dp[i+1][j][k-1] + cost < dp[i][j][k]) {
                        dp[i][j][k] = dp[i+1][j][k-1] + cost;
                        pre[i][j][k] = {j, k-1};
                    }
                }
                // 延续
                // 这里涉及到了一个字符串选择问题，3 = 1 + 2 + 1, 或者延续，那么前面第3个字符就需要对比
                // 可以确定一定是不一样的，比如 aaaa, aaab，可能dp[0][a][3]的最后的代价是一样的
                // dp[i][j][3], dp[i+1][j][2], dp[i+2][j][1], dp[i+3][j][3]
                if (dp[i+1][j][3] + cost < dp[i][j][3]) {
                    dp[i][j][3] = dp[i+1][j][3] + cost;
                    pre[i][j][3] = {j, 3};
                }
                else if (dp[i+1][j][3] + cost == dp[i][j][3] && pre[i][j][3].second == 2) {
                    // 这个时候必然是连接得到的
                    pii cur = {j, 3}; 
                    int tmp = i;
                    while (tmp < i+3) {
                        cur = pre[tmp][cur.first][cur.second];
                        tmp++;
                    }
                    if (cur.first > j) {
                        pre[i][j][3] = {j, 3};
                    }
                }
            }
        }
        int ans = inf;
        pii cur{-1, -1};
        string res;
        for (int i = 0; i < 26; ++i) {
            if (dp[0][i][3] < ans) {
                ans = dp[0][i][3];
                cur = {i, 3};
            }
        }
        if (cur.first == -1) return "";
        int p = 0;
        while (p < n) {
            res.push_back(char(cur.first + 'a'));
            cur = pre[p][cur.first][cur.second];
            p++;
        }
        return res;
    }
};