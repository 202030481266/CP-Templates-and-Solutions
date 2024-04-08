class Solution {
public:
    bool splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n < 6) return false; // 最少都分为了6个区域

        vector<int> sum(n + 1);
        for (int i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + nums[i];

        unordered_set<int> h;
        for (int i = 4; i <= n - 3; ++i) { // 枚举中间的节点
            h.clear();
            for (int j = 2; j < i - 1; ++j) {
                // [1, j) (j, i - 1]
                if (sum[j - 1] == sum[i - 1] - sum[j])
                    h.insert(sum[j - 1]);
            }
            for (int j = i + 2; j < n; ++j) {
                // [i + 1, j), (j, n]
                if (sum[j - 1] - sum[i] == sum[n] - sum[j] && h.count(sum[n] - sum[j]))
                    return true;
            }
        }
        return false;
    }
};