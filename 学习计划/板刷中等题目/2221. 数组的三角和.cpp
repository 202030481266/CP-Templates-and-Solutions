#include <bits/stdc++.h>
using namespace std;

static constexpr int maxn = 1001;

int dp[maxn][maxn];
bool flag = true;

void init() {
    for (int i = 0; i < maxn; ++i) {
        dp[i][0] = 1;
        dp[i][i] = 1;
    }
    for (int i = 1; i < maxn; ++i) {
        for (int j = 1; j < i; ++j) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % 10;
        }
    }
}

class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        if (flag) {
            init();
            flag = false;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = (ans + dp[n - 1][i] * nums[i] % 10) % 10;
        }
        return ans;
    }
};