#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        // 最长的非递减数组
        int n = nums1.size();
        vector<vector<int>> a{nums1, nums2};
        vector dp(n+1, vector<int>(2));
        dp[0][1] = dp[0][0] = 1;
        for (int i = 1; i < n; ++i) {
            if (a[0][i] >= a[0][i-1]) dp[i][0] = max(dp[i][0], dp[i-1][0]);
            if (a[0][i] >= a[1][i-1]) dp[i][0] = max(dp[i][0], dp[i-1][1]);
            if (a[1][i] >= a[0][i-1]) dp[i][1] = max(dp[i][1], dp[i-1][0]);
            if (a[1][i] >= a[1][i-1]) dp[i][1] = max(dp[i][1], dp[i-1][1]);
            dp[i][0] += 1;
            dp[i][1] += 1;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, max(dp[i][0], dp[i][1]));
        }
        return ans;
    }
};