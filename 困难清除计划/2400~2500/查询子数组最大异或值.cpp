#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// very easy dp problem compare to LCP hard problems
// 10 level is fake

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), val[n][n], dp[n][n];
        memset(dp, 0, sizeof(dp));
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (len == 1) val[i][i] = nums[i];
                else val[i][j] = val[i][j-1] ^ val[i+1][j];
            }
        }
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (len == 1) dp[i][i] = val[i][i];
                else dp[i][j] = max(max(dp[i][j-1], dp[i+1][j]), val[i][j]);
            }
        }
        vector<int> ans;
        for (auto q : queries) ans.push_back(dp[q[0]][q[1]]);
        return ans;
    }
};