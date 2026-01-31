#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 拆位置的方法，本质上没有得到复杂度的优化
class Solution {
public:
    int minXor(vector<int>& nums, int k) {
        const int n = nums.size();
        int m = 0;
        for (int v : nums)                    
            m = max(m, 32 - __builtin_clz(v));

        vector<int> pxor(n + 1);
        for (int i = 1; i <= n; ++i) pxor[i] = pxor[i - 1] ^ nums[i - 1];

        int ans = 0;
        vector<vector<char>> dp(k + 1, vector<char>(n + 1));

        for (int b = m - 1; b >= 0; --b) {
            for (int t = 0; t <= k; ++t)
                fill(dp[t].begin(), dp[t].end(), 0);
            dp[0][0] = 1;

            const int ansHigh = ans >> (b + 1);          

            for (int i = 1; i <= n; ++i) {
                for (int seg = 1; seg <= k && seg <= i; ++seg) {
                    for (int j = seg - 1; j < i; ++j) if (dp[seg - 1][j]) {
                        int sub  = pxor[i] ^ pxor[j];     
                        int high = sub >> (b + 1);

                        if (high < ansHigh) {             
                            dp[seg][i] = 1; break;
                        }
                        if (high == ansHigh && ((sub >> b) & 1) == 0) {
                            dp[seg][i] = 1; break;        
                        }
                    }
                }
            }
            if (!dp[k][n]) ans |= (1 << b);               
        }
        return ans;
    }
};


// 最为简单的做法
int dp[300][300];

class Solution {
public:
    int minXor(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) dp[i][j] = (1<<30);
        }
        dp[0][0] = 0;
        vector<int> sum(n + 1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] ^ nums[i];
        }
        for (int i = 1; i <= n; ++i) {
            for (int x = 1; x <= k; ++x) {
                for (int j = 0; j < i ; ++j) {
                    dp[i][x] = min(dp[i][x], max(sum[i] ^ sum[j], dp[j][x - 1]));
                }
            }
        }
        return dp[n][k];
    }
};