class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        int n = prob.size();
        double dp[n][target + 2];
        
        dp[0][0] = 1 - prob[0];
        dp[0][1] = prob[0];
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= target; ++j) {
                dp[i][j] = dp[i - 1][j] * (1 - prob[i]);
                if (j > 0) dp[i][j] += dp[i - 1][j - 1] * prob[i];
            }
        }
        return dp[n - 1][target];
    }
};