class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int a = -prices[0], b = -prices[0], c = 0;
        for (int i = 1; i < n; ++i) {
            int aa = a, bb = b, cc = c;
            aa = max(aa, c - prices[i]);   
            bb = max(bb, a + prices[i]);
            cc = max(cc, b);
            a = aa, b = bb, c = cc;
        }
        return max(a, max(b, c));
    }
};