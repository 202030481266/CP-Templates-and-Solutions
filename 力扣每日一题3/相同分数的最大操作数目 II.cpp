#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size(), dp[n][n];
        if (n < 2) return 0;
        auto cal = [&](int s, int st, int ed) -> int {
            // [st,ed]
            if (st > ed) return 0;
            memset(dp, 0, sizeof(dp));
            for (int len = 2; len <= ed-st+1; ++len) {
                for (int i = st; i + len - 1 <= ed; ++i) {
                    int j = i + len - 1;
                    if (len == 2) {
                        dp[i][j] = (nums[i] + nums[j] == s ? 1 : 0);
                    }
                    else {
                        if (nums[i]+nums[i+1] == s) dp[i][j] = max(dp[i][j], dp[i+2][j]+1);
                        if (nums[j]+nums[j-1] == s) dp[i][j] = max(dp[i][j], dp[i][j-2]+1);
                        if (nums[i]+nums[j] == s) dp[i][j] = max(dp[i][j], dp[i+1][j-1]+1);
                    }
                }
            }
            return dp[st][ed];
        };
        int r1=cal(nums[0]+nums[1],2,n-1), r2=cal(nums[n-1]+nums[n-2],0,n-3),r3=cal(nums[0]+nums[n-1],1,n-2); 
        return max({r1,r2,r3})+1;
    }
};