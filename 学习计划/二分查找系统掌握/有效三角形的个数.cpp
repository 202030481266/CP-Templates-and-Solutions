// 哈希表是更加快速的做法
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> sum(mx + 1);
        for (int& v : nums) if (v) ++sum[v];
        for (int i = 1; i <= mx; ++i) sum[i] += sum[i - 1];
        int ans = 0;
        for (int i = 1; i <= mx; ++i) {
            int n = sum[i] - sum[i - 1], s = min(2 * i - 1, mx);
            if (!n) continue;
            ans += n * (n - 1) / 2 * (sum[s] - sum[i] + sum[i - 1]);
            ans += n * (n - 1) * (n - 2) / 6;
            for (int j = 1; j < i; ++j) {
                int m = sum[j] - sum[j - 1], ss = min(i + j - 1, mx);
                ans += m * n * (sum[ss] - sum[i]);
            }
        }
        return ans;
    }
};