class Solution {
    typedef long long ll;
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        ll odd = 0, even = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, odd - nums[i]);
            ans = max(ans, even + nums[i]);
            ll od = odd, ev = even;
            odd = max(odd, ev + nums[i]);
            even = max(even, od - nums[i]);
        }
        return ans;
    }
};