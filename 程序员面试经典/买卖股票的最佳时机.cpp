class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mn = prices[0], ans = 0, n = prices.size();
        for (int i = 1; i < n; ++i) {
            ans = max(ans, prices[i] - mn);
            mn = min(mn, prices[i]);
        }
        return ans;
    }
};