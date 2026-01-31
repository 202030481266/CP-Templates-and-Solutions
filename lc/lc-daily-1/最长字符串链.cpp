class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int n = words.size(), dp[n], ans = 0;
        memset(dp, 0, sizeof(dp));
        // 按照长度排序之后转换为最长上升子序列问题
        sort(words.begin(), words.end(), [&](const auto& x, const auto& y) {return x.size() < y.size();});
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (words[j].size() + 1 == words[i].size()) {
                    int x = 0, y = 0, c = 1;
                    while (x < words[j].size() && y < words[i].size()) {
                        if (words[j][x] == words[i][y]) ++x, ++y;
                        else if (c) c = 0, ++y;
                        else break;
                    }
                    if (c && y < words[i].size()) ++y;
                    if (y == words[i].size() && x == words[j].size()) dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};