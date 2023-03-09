// https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended-ii/



class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();

        sort(events.begin(), events.end(), [&](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });
        vector<int> pre(n);
        vector<int> right;
        pre[0] = -1;
        right.emplace_back(events[0][1]);
        for (int i = 1; i < n; ++i) {
            auto it = lower_bound(right.begin(), right.end(), events[i][0]);
            if (it == right.end()) {
                pre[i] = i - 1;
            }
            else {
                if (it == right.begin()) pre[i] = -1;
                else pre[i] = (it - right.begin()) - 1;
            }
            right.emplace_back(events[i][1]);
        }
        vector dp(n, vector<int>(k + 1));
        dp[0][1] = events[0][2];
        for (int i = 1; i < n; ++i) {
            dp[i][1] = max(dp[i - 1][1], events[i][2]);
            for (int j = 2; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (pre[i] >= 0 && (dp[pre[i]][j - 1] > 0 || j == 1)) {
                    // it should be > 0
                    dp[i][j] = max(dp[pre[i]][j - 1] + events[i][2], dp[i][j]);
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= k; ++i) ans = max(ans, dp[n - 1][i]);
        return ans;
    }
};