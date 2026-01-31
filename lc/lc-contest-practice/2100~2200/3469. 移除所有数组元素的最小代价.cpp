#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// 非常好的思维题目，动态规划解法
// 这道题目思维难度远大于t4，而且子结构比较隐晦

class Solution {
public:
    int minCost(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1, inf);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int sum = 0;
            if (i&1) {
                for (int j = i-2; j >= 1; --j) {
                    if (j&1) {
                        dp[i] = min(dp[i], dp[j-1] + sum + max(nums[j-1], nums[i-1]));
                    }
                    else {
                        dp[i] = min(dp[i], dp[j+1] + max(nums[j-1], nums[i-1]) + sum);
                        sum += max(nums[j-1], nums[j]);
                    }
                }
            }
            else {
                for (int j = i-1; j >= 1; --j) {
                    if (j&1) {
                        dp[i] = min(dp[i], dp[j-1] + sum + max(nums[j-1], nums[i-1]));
                    }
                    else {
                        dp[i] = min(dp[i], dp[j+1] + max(nums[j-1], nums[i-1]) + sum);
                        sum += max(nums[j-1], nums[j]);
                    }
                }
            }
        }
        int ans = inf;
        if (n&1) {
            int sum = 0;
            for (int i = n; i >= 1; --i) {
                if (i&1) {
                    ans = min(ans, dp[i-1] + nums[i-1] + sum);
                }
                else {
                    ans = min(ans, dp[i+1] + sum + nums[i-1]);
                    sum += max(nums[i-1], nums[i]);
                }
            }
        }
        else ans = dp[n];
        return ans;
    }
};