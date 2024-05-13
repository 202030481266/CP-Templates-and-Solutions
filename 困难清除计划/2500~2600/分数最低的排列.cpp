#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findPermutation(vector<int>& nums) {
        // 最小字典序
        int n = nums.size(), dp[n][n][1<<n];
        // 环状的dp，固定开始的第一个数字，然后做n次
        memset(dp, 0x3f, sizeof(dp));
        vector<int> g[n+1]; 
        // 按照状态数中的1来进行分组
        for (int i = 0; i < (1<<n); ++i) {
            int cnt = __builtin_popcount(i);
            g[cnt].push_back(i);
        }
        // 从后面开始计算,找到字典序
        // 然而，注意到了循环的性质，对于一个排列而言，左移任意次结果不变，所以排列的起始一定是0，这一点是这道题最关键的点
        // 将数字0直接放到n-1位置上
        int N = (1<<n) - 1;
        for (int i = 1; i < n; ++i) {
            dp[0][i][1<<i] = abs(i - nums[0]);
        }
        for (int i = 1; i < n - 1; ++i) {
            for (int&s : g[i+1]) {
                if (s & 1) continue; // 0必须在最后
                for (int j = 1; j < n; ++j) {
                    if (s & (1<<j)) {
                        for (int k = 1; k < n; ++k) {
                            if (k != j && (s & (1<<k))) {
                                if (dp[i][j][s] > dp[i-1][k][s ^ (1<<j)] + abs(j - nums[k])) {
                                    dp[i][j][s] = dp[i-1][k][s ^ (1<<j)] + abs(j - nums[k]);
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            dp[n-1][0][N] = min(dp[n-1][0][N], dp[n-2][i][N ^ 1] + nums[i]);
        }
        vector<int> ans{0};
        // 正向遍历很难找到字典序，所以反向遍历
        int last = 0, cur = N ^ 1;
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 1; j < n; j++) {
                if ((cur & (1<<j)) && dp[i][j][cur] + abs(last - nums[j]) == dp[i+1][last][cur | (1<<last)]) {
                    ans.push_back(j);
                    last = j;
                    cur ^= (1<<j);
                    break;
                }
            }
        }
        return ans;
    }
};
