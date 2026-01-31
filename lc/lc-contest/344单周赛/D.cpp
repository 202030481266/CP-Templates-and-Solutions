class Solution {
public:
    int minIncrements(int n, vector<int> &cost) {
        int ans = 0;
        for (int i = n / 2; i; i--) { // 从最后一个非叶节点开始算
            ans += abs(cost[i * 2 - 1] - cost[i * 2]); // 两个子节点变成一样的
            cost[i - 1] += max(cost[i * 2 - 1], cost[i * 2]); // 累加路径和
        }
        return ans;
    }
};

