class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        multiset<int> s;
        // [0, x, 2 * x]
        int n = nums.size(), ans = INT_MAX;
        for (int i = x; i < n; ++i) {
            s.insert(nums[i - x]);
            auto it = s.lower_bound(nums[i]);
            if (it!=s.end()) ans = min(ans, *it-nums[i]);
            if (it!= s.begin()) ans = min(ans, nums[i]-*prev(it));
        }
        return ans;
    }
};