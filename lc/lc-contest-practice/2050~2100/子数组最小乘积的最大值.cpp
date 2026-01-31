// https://leetcode.cn/problems/maximum-subarray-min-product/



class Solution {
public:
    static constexpr int mod = 1e9 + 7;
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();

        vector<int> left(n), right(n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && nums[s.top()] >= nums[i]) {
                s.pop();
            }
            left[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }
        s = stack<int>();
        for (int  i = n - 1; i >= 0; --i) {
            while (!s.empty() && nums[s.top()] >= nums[i]) {
                s.pop();
            }
            right[i] = s.empty() ? n : s.top();
            s.push(i);
        }
        vector<long long> sum(n);
        sum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + nums[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int l = left[i] + 1, r = right[i] - 1;
            long long res = 0;
            if (l == 0) res = sum[r];
            else res = sum[r] - sum[l - 1];
            ans = max(ans, res * nums[i]);
        }
        return ans % mod;
    }
};