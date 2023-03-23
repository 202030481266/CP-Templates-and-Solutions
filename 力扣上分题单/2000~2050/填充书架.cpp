// https://leetcode.cn/problems/filling-bookcase-shelves/



class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();

        vector<int> dp(n + 1);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + books[i - 1][1];
            int sum = books[i - 1][0], maxx = books[i - 1][1];
            for (int j = i - 1; j >= 1; --j) {
                if (sum + books[j - 1][0] > shelfWidth) break;
                sum += books[j - 1][0];
                maxx = max(maxx, books[j - 1][1]);
                dp[i] = min(dp[i], dp[j - 1] + maxx);
            }
        }
        return dp[n];
    }
};