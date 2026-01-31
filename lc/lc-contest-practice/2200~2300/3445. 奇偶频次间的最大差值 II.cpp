#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int maxDifference(string s, int k) {
        // 0, 1表示偶数，奇数，2表示0
        int n = s.size(), dp[n][5][5][3][3];
        memset(dp, -0x3f, sizeof(dp));
        for (int i = 0; i < 5; ++i) {
            if (i == s[0] - '0') continue;
            dp[0][s[0]-'0'][i][1][2] = 1;
            dp[0][i][s[0]-'0'][2][1] = -1;
        }
        // 计算dp
        for (int i = 1; i < n; ++i) {
            int num = s[i] - '0';
            for (int p = 0; p < 5; ++p) {
                for (int q = 0; q < 5; ++q) {
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            dp[i][p][q][x][y] = dp[i-1][p][q][x][y];
                        }
                    }
                }
            }
            // 连接后面的字符串，num的个数只能是1或者0，如果是1有可能是从前面的为0的状态提供的
            for (int j = 0; j < 5; ++j) {
                if (j == num) continue;
                // 假设都是不为0的状态转移
                for (int x = 0; x < 2; ++x) {
                    for (int y = 0; y < 2; ++y) {
                        dp[i][num][j][x][y] = dp[i][j][num][x][y] = -inf; // 初始化为-inf，从而方便转移，强制选择
                        if (x == 1 && dp[i-1][num][j][2][y] != -inf)
                            dp[i][num][j][x][y] = max(dp[i][num][j][x][y], dp[i-1][num][j][2][y] + 1);
                        if (y == 1 && dp[i-1][j][num][x][2] != -inf) 
                            dp[i][j][num][x][y] = max(dp[i][j][num][x][y], dp[i-1][j][num][x][2] - 1);
                        if (dp[i-1][num][j][x ^ 1][y] != -inf)
                            dp[i][num][j][x][y] = max(dp[i][num][j][x][y], dp[i-1][num][j][x ^ 1][y] + 1);
                        if (dp[i-1][j][num][x][y ^ 1] != -inf)
                            dp[i][j][num][x][y] = max(dp[i][j][num][x][y], dp[i-1][j][num][x][y ^ 1] - 1);
                    }
                }
                // 其中一个为0
                for (int x = 0; x < 2; ++x) {
                    dp[i][num][j][x][2] = dp[i][j][num][2][x] = -inf;
                    if (dp[i-1][num][j][x ^ 1][2] != -inf)
                        dp[i][num][j][x][2] = max(dp[i][num][j][x][2], dp[i-1][num][j][x ^ 1][2] + 1);
                    if (dp[i-1][j][num][2][x ^ 1] != -inf)
                        dp[i][j][num][2][x] = max(dp[i][j][num][2][x], dp[i-1][j][num][2][x ^ 1] - 1);
                }
                // 不连接后面的字符串
                for (int j = 0; j < 5; ++j) {
                    if (j == num) continue;
                    dp[i][num][j][1][2] = max(dp[i][num][j][1][2], 1);
                    dp[i][j][num][2][1] = max(dp[i][j][num][2][1], -1);
                }
                for (int x = 0; x < 3; ++x) {
                    dp[i][num][j][2][x] = dp[i][j][num][x][2] = -inf; // 不合法的
                }
            }
        }
        vector<int> cnt(5);
        int l = 0, ans = -inf;
        for (int i = 0; i < n; ++i) {
            int num = s[i] - '0';
            cnt[num]++;
            while (i-l+1 > k) {
                cnt[s[l++]-'0']--;
            }
            // fre[x] - fre[y]
            if (i-l+1 >= k) {
                for (int x = 0; x < 5; ++x) {
                    for (int y = 0; y < 5; ++y) {
                        // 不取后面的字符
                        int t1 = (cnt[x] & 1), t2 = (cnt[y] & 1);
                        if (cnt[x] > 0 && cnt[y] > 0 && t1 && !t2) {
                            ans = max(ans, cnt[x] - cnt[y]);
                        }
                        if (l-1 >= 0) {
                            // 后面的位置只存在一种字符的情况
                            if (cnt[x] > 0 && t1 && dp[l-1][x][y][2][t2] != -inf) {
                                ans = max(ans, cnt[x] - cnt[y] + dp[l-1][x][y][2][t2]);
                            }
                            if (cnt[y] > 0 && !t2 && dp[l-1][x][y][t1 ^ 1][2] != -inf) {
                                ans = max(ans, cnt[x] - cnt[y] + dp[l-1][x][y][t1 ^ 1][2]);
                            }
                            // 后面存在两种字符
                            if (dp[l-1][x][y][t1 ^ 1][t2] != -inf) {
                                ans = max(ans, dp[l-1][x][y][t1 ^ 1][t2] + cnt[x] - cnt[y]);
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};