// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/description/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        // 二分查找的上下界
        int left = 1, right = *max_element(prices.begin(), prices.end());
        // 存储答案，如果值为 -1 表示二分查找失败
        int ans = -1;
        while (left <= right) {
            // 二分得到当前的斜率（手续费）
            int c = (left + right) / 2;

            // 使用与 714 题相同的动态规划方法求解出最大收益以及对应的交易次数
            int buyCount = 0, sellCount = 0;
            int buy = -prices[0], sell = 0;

            for (int i = 1; i < n; ++i) {
                if (sell - prices[i] >= buy) {
                    buy = sell - prices[i];
                    buyCount = sellCount;
                }
                if (buy + prices[i] - c >= sell) {
                    sell = buy + prices[i] - c;
                    sellCount = buyCount + 1;
                }
            }

            // 如果交易次数大于等于 k，那么可以更新答案
            // 这里即使交易次数严格大于 k，更新答案也没有关系，因为总能二分到等于 k 的
            if (sellCount >= k) {
                // 别忘了加上 kc
                ans = sell + k * c;
                left = c + 1;
            }
            else {
                right = c - 1;
            }
        }

        // 如果二分查找失败，说明交易次数的限制不是瓶颈
        // 可以看作交易次数无限，直接使用贪心方法得到答案
        if (ans == -1) {
            ans = 0;
            for (int i = 1; i < n; ++i) {
                ans += max(prices[i] - prices[i - 1], 0);
            }
        }

        return ans;
    }
};