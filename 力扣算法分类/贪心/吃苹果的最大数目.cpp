// https://leetcode.cn/problems/maximum-number-of-eaten-apples/I
// 贪心策略：每一次都先把最快过期的苹果吃了永远不吃亏


class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = apples.size();
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;

        int ans = 0;
        int i = 1;
        while (i <= n || !q.empty()) {
            // put some apples
            if (i <= n && apples[i - 1]) {
                q.emplace(i + days[i - 1], apples[i - 1]);
            }
            
            // throw the expired apples
            while (!q.empty() && q.top().first <= i) q.pop();

            // find apples to eat
            if (!q.empty()) {
                auto u = q.top();
                q.pop();
                ++ans;
                if (u.second > 1) q.emplace(u.first, u.second - 1);
            }

            ++i;
        }
        return ans;
    }
};