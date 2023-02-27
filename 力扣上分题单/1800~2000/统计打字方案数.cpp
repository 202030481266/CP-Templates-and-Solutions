class Solution {
public:
    static constexpr int mod = 1000000007;

    int countTexts(string pressedKeys) {

        auto f = [&](int N, int v) {
            vector<long long> dp(N + 1, 0);
            dp[0] = 1;
            int prefix = ((v == 7 || v == 9) ? 4 : 3);
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= prefix; ++j) {
                    if (i - j >= 0)
                        dp[i] = (dp[i] + dp[i - j]) % mod;
                }
            }
            return dp[N] % mod;
        };

        long long ans = 1;
        int n = pressedKeys.size();
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j < n && pressedKeys[j] == pressedKeys[i]) ++j;
            ans = (ans * f(j - i, pressedKeys[i] - '0')) % mod;
            i = j - 1;
        }
        return ans;
    }
};