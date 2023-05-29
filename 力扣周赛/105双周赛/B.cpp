class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        unordered_map<string, bool> h;
        for (auto &c : dictionary) h[c] = true;
        int n = s.size(), dp[n + 1][2];
        memset(dp, 0x3f, sizeof(dp));
        vector<int> pos[n + 1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                string tmp = s.substr(j, i - j + 1);
                if (h[tmp]) pos[i + 1].emplace_back(j + 1); // offset
            }
        }
        dp[0][0] = dp[0][1] = 0;
        for (int i = 1; i <= n; ++i) {
            if (dp[i - 1][0] != 0x3f3f3f3f) dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
            if (dp[i - 1][1] != 0x3f3f3f3f) dp[i][0] = min(dp[i][0], dp[i - 1][1] + 1);
            for (int j : pos[i]) {
                // [j, i] is deleted
                int k = j - 1;
                if (dp[k][0] != 0x3f3f3f3f) dp[i][1] = min(dp[i][1], dp[k][0]);
                if (dp[k][1] != 0x3f3f3f3f) dp[i][1] = min(dp[i][1], dp[k][1]);
            }
        }
        return min(dp[n][0], dp[n][1]);
    }
};