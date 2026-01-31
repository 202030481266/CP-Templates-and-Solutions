class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int a = -prices[0] - fee, b = 0;
        for (int i = 1; i < n; ++i) {
            int aa = a, bb = b;
            aa = max(aa, b - prices[i] - fee);
            bb = max(bb, a + prices[i]);
            a = aa, b = bb;
        }
        return max(a, b);
    }
};