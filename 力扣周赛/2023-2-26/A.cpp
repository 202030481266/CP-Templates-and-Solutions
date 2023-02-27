class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(n + 2, 0), b(n + 2, 0);

        for (int i = 1; i <= n; ++i) a[i] = a[i - 1] + nums[i - 1];
        for (int i = n; i >= 1; --i) b[i] = b[i + 1] + nums[i - 1];

        vector<int> ans;
        for (int i = 1; i <= n; ++i) 
            ans.emplace_back(abs(a[i - 1] - b[i + 1]));
        return ans;
    }
};