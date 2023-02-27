// https://leetcode.cn/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/


class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int n = candiesCount.size();
        vector<long long> sum(n + 1, 0);
        vector<bool> ans;

        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + candiesCount[i - 1];
        for (auto q : queries) {
            ++q[1];
            long long a = 1ll * (q[1] - 1);
            long long b = 1ll * q[1] * q[2];
            // 有两种极端的情况
            // 还没有到day之前就把所有的条件糖果吃完了,糖果太少了 a >= sum[q[0] + 1];
            // 在条件日之前永远无法吃到条件糖果，糖果太多了, b <= sum[q[0]]
            ans.emplace_back(a < sum[q[0] + 1] && b > sum[q[0]]);
        }
        return ans;
    }
};