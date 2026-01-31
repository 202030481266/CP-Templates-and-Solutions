class Solution {
public:
    int findMin(vector<int>& nums) {
        // 一定存在一个index使得[0, index - 1]>=nums[0],[index, n - 1]<nums[0]
        int l = 0, r = nums.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] >= nums[0]) l = mid;
            else r = mid;
        }
        return l + 1 < nums.size() ? nums[l + 1] : nums[0]; 
    }
};