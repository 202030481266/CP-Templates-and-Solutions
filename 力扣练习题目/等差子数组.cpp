// https://leetcode.cn/problems/arithmetic-subarrays/



class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        // n <= 500, m <= 500
        int n = nums.size(), m = l.size();

        vector<bool> ans(m);

        for (int i = 0; i < m; ++i) {
            vector<int> a;
            for (int j = l[i]; j <= r[i]; ++j)
                a.emplace_back(nums[j]);
            sort(a.begin(), a.end());
            int sub = a[1] - a[0];
            bool flag = true;
            for (int j = 2; j < a.size(); ++j) {
                if (a[j] - a[j - 1] != sub) {
                    flag = false;
                    break;
                }
            }
            ans[i] = flag;
        }
        return ans;
    }
};