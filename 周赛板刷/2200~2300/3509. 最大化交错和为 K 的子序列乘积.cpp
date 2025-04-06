#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size(), m = accumulate(nums.begin(), nums.end(),0), f[2][2][2][2*m+1];
        if (k < -m || k > m) return -1;
        int cntones = 0;
        for (int v : nums) {
            if (v == 1) {
                ++cntones;
            }
        }
        m = min(m, 50 + cntones); // 限定了值域，因为乘积的影响，这是本题目的关键
        if (abs(k) <= m) {
            int dp[2][2][m*2+1][limit+1];
            memset(dp, 0, sizeof(dp));
            int pre = 0, cur = 1;
            for (int i = 0; i < n; ++i) {
                // copy pre -> cur
                if (nums[i] <= limit) {
                    memcpy(dp[cur], dp[pre], sizeof(dp[0]));
                    dp[cur][0][nums[i] + m][nums[i]] = 1;
                    if (nums[i] > 0) {
                        for (int j = m * 2; j >= 0; --j) {
                            for (int mul = limit / nums[i] * nums[i]; mul >= nums[i]; mul -= nums[i]) {
                                if (j + nums[i] <= m * 2) {
                                    dp[cur][1][j][mul] |= dp[pre][0][j + nums[i]][mul / nums[i]];
                                }
                                if (j - nums[i] >= 0) {
                                    dp[cur][0][j][mul] |= dp[pre][1][j - nums[i]][mul / nums[i]];
                                }
                            }
                        }
                    }
                    else if (nums[i] == 0) {
                        for (int j = m * 2; j >= 0; --j) {
                            for (int mul = limit; mul >= 0; --mul) {
                                dp[cur][1][j][0] |= dp[pre][0][j][mul];
                                dp[cur][0][j][0] |= dp[pre][1][j][mul];
                            }
                        }
                    }
                    swap(pre, cur);
                }
            }
            for (int i = limit; i >= 0; --i) {
                if (dp[pre][0][m + k][i] || dp[pre][1][m + k][i]) {
                    return i;
                }
            }
        }
        // 检查0
        memset(f, 0, sizeof(f));
        int pre = 0, cur = 1;
        for (int i = 0; i < n; ++i) {
            memcpy(f[cur], f[pre], sizeof(f[0]));
            if (nums[i]) {
                f[cur][0][0][nums[i] + m] = 1;
                for (int j = 2 * m; j >= 0; --j) {
                    if (j + nums[i] <= 2 * m) {
                        f[cur][1][0][j] |= f[pre][0][0][j+nums[i]];
                        f[cur][1][1][j] |= f[pre][0][1][j+nums[i]];
                    }
                    if (j - nums[i] >= 0) {
                        f[cur][0][0][j] |= f[pre][1][0][j-nums[i]];
                        f[cur][0][1][j] |= f[pre][1][1][j-nums[i]];
                    }
                }
            }
            else {
                f[cur][0][1][m] = 1;
                for (int j = 2 * m; j >= 0; --j) {
                    f[cur][1][1][j] |= f[pre][0][1][j]; 
                    f[cur][1][1][j] |= f[pre][0][0][j];
                    f[cur][0][1][j] |= f[pre][1][1][j];
                    f[cur][0][1][j] |= f[pre][1][0][j];
                }
            }
            swap(pre, cur);
        }
        return (f[pre][0][1][k+m] || f[pre][1][1][k+m]? 0 : -1);
    }
};