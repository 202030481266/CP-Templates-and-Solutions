// https://leetcode.cn/problems/minimum-distance-to-type-a-word-using-two-fingers/



class Solution {
public:
    int minimumDistance(string word) {
        int n = word.size();
        vector dp(n + 1, vector(30, vector<int>(30, 0x3f3f3f3f)));

        auto f = [&](int st, int ed) -> int {
            if (st == 0 || ed == 0) {
                return 0;
            }
            --st, --ed;  // 'A' start with 1
            int x1 = st / 6, y1 = st % 6;
            int x2 = ed / 6, y2 = ed % 6;
            return abs(x1 - x2) + abs(y1 - y2);
        };

        dp[1][word[0] - 'A' + 1][0] = 0;
        dp[1][0][word[0] - 'A' + 1] = 0;

        for (int i = 2; i <= n; ++i) {
            for (int x = 0; x <= 26; ++x) {
                for (int y = 0; y <= 26; ++y) {
                    // use the first finger
                    // dp[i - 1][x][y] -> dp[i][word[i - 1]-'A'+1][y]+dis1
                    // use the second finger
                    // dp[i - 1][x][y] -> dp[i][x][word[i - 1]-'A'+1]+dis2
                    if (dp[i - 1][x][y] != 0x3f3f3f3f) {
                        // it means that it is a valid status
                        int tmp = word[i - 1] - 'A' + 1;
                        dp[i][tmp][y] = min(dp[i][tmp][y], dp[i - 1][x][y] + f(tmp, x));
                        dp[i][x][tmp] = min(dp[i][x][tmp], dp[i - 1][x][y] + f(tmp, y));
                    }
                }
            }
        }
        int ans = INT_MAX, tmp = word[n - 1] - 'A' + 1;
        for (int x = 0; x <= 26; ++x) {
            ans = min(ans, dp[n][tmp][x]);
            ans = min(ans, dp[n][x][tmp]);
        }
        return ans;
    }
};