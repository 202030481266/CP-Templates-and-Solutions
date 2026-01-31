class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {

        // 最长的重复子序列问题
        int n = s2.size(), m = s1.size();
        vector<int> dp(n);

        for (int i = 0; i < n; ++i) {
            int p = i;
            for (int j = 0; j < m; ++j) {
                if (s1[j] == s2[p]) {
                    p = (p + 1) % n;
                    ++dp[i];
                }
            }
        }

        int pre = 0, cur;
        for (int i = 0; i < n1; ++i) {
            cur = pre + dp[pre % n];
            pre = cur;
        }

        // m * n2
        return pre / n / n2;
    }
};