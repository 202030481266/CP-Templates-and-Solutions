// https://leetcode.cn/problems/minimum-difficulty-of-a-job-schedule/



class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        // this is impossible to finish
        if (n < d) return -1;

        vector dp(n + 1, vector<int>(d + 1, 0x3f3f3f3f));
        vector maxx(n + 1, vector<int>(n + 1));
        for (int i = 0; i < n; ++i) {
            int mx = jobDifficulty[i];
            for (int j = i; j < n; ++j) {
                mx = max(mx, jobDifficulty[j]);
                maxx[i][j] = mx;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= d; ++j) {
                if (j == 1) {
                    dp[i][1] = maxx[0][i];
                }
                else {
                    // 0 ... j - 2
                    // 0 ... k is the j - 1 group, and k + 1 .... i is the j group
                    for (int k = max(j - 2, 0); k < i; ++k) {
                        dp[i][j] = min(dp[i][j], dp[k][j - 1] + maxx[k + 1][i]);
                    }
                }
            }
        }
        return dp[n - 1][d];
    }
};