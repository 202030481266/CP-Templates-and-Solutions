#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxHammingDistances(vector<int>& nums, int m) {
        // 值域思考,最长距离转换为反码的最短距离
        // 最长无法使用图算法高效解决，但是最短距离可以
        int n = nums.size(), dp[1<<m];
        memset(dp, 0x3f, sizeof(dp));
        vector<int> q;
        for (int i = 0; i < n; ++i) {
            dp[nums[i]] = 0;
            q.push_back(nums[i]);
        }
        for (int dis = 1; !q.empty(); ++dis) {
            vector<int> tmp;
            for (int v : q) {
                for (int i = 0; i < m; ++i) {
                    int u = v ^ (1 << i);
                    if (dp[u] > dis) {
                        dp[u] = dis;
                        tmp.push_back(u);
                    }
                }
            }
            q = move(tmp);
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = m - dp[(1<<m)-1 ^ nums[i]];
        return ans;
    }
};
