class Solution {
public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        int n = nums.size(), mx = 0; 
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            mx = max(mx, nums[i]);
            a[i] = mx + nums[i];
            if (i > 0) a[i] += a[i - 1];
        }
        return a;
    }
};