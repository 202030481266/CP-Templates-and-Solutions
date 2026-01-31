class Solution {
public:
    vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
        int n = groups.size(), dis[n][n], dp[n], pre[n];

        memset(dis, 0x3f, sizeof(dis));
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (words[i].size() == words[j].size()) {
                    dis[i][j] = 0;
                    for (int k = 0; k < words[i].size(); ++k)
                        if (words[i][k] != words[j][k]) ++dis[i][j];
                }

        memset(pre, -1, sizeof(pre));
        memset(dp, 0, sizeof(dp));
        int mx = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (dis[j][i] == 1 && groups[j] != groups[i] && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
            }
            mx = max(mx, dp[i]);
        }
        int cur = -1;
        for (int i = 0; i < n; ++i) 
            if (dp[i] == mx) {
                cur = i;
                break;
            }
        vector<string> ans;
        while (cur != -1) {
            ans.push_back(words[cur]);
            cur = pre[cur];
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};