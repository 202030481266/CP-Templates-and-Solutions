// 模拟
class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size(), cost[n][n];
        memset(cost, 0x3f, sizeof(cost));
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            cost[0][i] = nums[i];
            ans += cost[0][i];
        }
        for (int i = 1; i < n; ++i) {
            long long tmp = 0;
            for (int j = 0; j < n; ++j) {
                cost[i][j] = min(cost[i - 1][j], nums[(j - i + n) % n]);
                tmp += cost[i][j];
            }
            ans = min(ans, tmp + 1ll * i * x);
        }
        return ans;
    }
};