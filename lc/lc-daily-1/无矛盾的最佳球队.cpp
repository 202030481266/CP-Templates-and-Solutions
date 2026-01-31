// https://leetcode.cn/problems/best-team-with-no-conflicts/



class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int, int>> a;

        for (int i = 0; i < n; ++i)
            a.emplace_back(ages[i], scores[i]);
        sort(a.begin(), a.end());

        // dp
        vector<int> dp(n);
        dp[0] = a[0].second;
        for (int i = 1; i < n; ++i) {
            dp[i] = a[i].second;
            for (int j = 0; j < i; ++j) {
                if (a[i].first == a[j].first) {
                    dp[i] = max(dp[i], dp[j] + a[i].second);
                }
                else if (a[i].second >= a[j].second) {
                    dp[i] = max(dp[i], dp[j] + a[i].second);
                }
            }
        }
        int ans = INT_MIN;
        for (int i = 0; i < n; ++i) ans = max(ans, dp[i]);
        return ans;
    }
};