class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), have = -0x3f3f3f3f, empty = 0;
        
        for (int i = 0; i < n; ++i) {
            int n_empty = max(have + prices[i], empty);
            int n_have = max(empty - prices[i], have);
            have = n_have;
            empty = n_empty;
        }
        return max(have, empty);
    }
};