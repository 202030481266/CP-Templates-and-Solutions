// https://leetcode.cn/problems/increasing-triplet-subsequence/
// 贪心，在相同的满足条件下，让子序列的左边尽可能小，右边尽可能大
// 最长上升子序列也是一样的的贪心策略


class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(3, INT_MAX);
        for(int i = 0; i < n; i++){
            int t = nums[i];
            if(f[2] < t) return true;
            else if(f[1] < t and t < f[2]) f[2] = t;
            else if(f[1] > t) f[1] = t;
        }
        return false;
    }
};