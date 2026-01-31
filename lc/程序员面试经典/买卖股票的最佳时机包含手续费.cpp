class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int have = -prices[0], empty = 0;
        for (int i = 1; i < n; ++i) {
            int n_have = max(have, empty - prices[i]);
            int n_empty = max(empty, have + prices[i] - fee);
            empty = n_empty;
            have = n_have;
        }
        return max(have, empty);
    }
};