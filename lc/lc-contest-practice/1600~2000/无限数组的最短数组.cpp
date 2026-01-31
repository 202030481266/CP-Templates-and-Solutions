// 考虑鸽巢原理 + 环形数组 + 滑动窗口
class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        // 个人觉得这道题可以作为2000分
        long long sum = accumulate(nums.begin(), nums.end(), 0ll);
        int n = nums.size();
        int ans = (target / sum) * n; 
        target %= sum;

        vector<int> arr(n * 2);
        for (int i = 0; i < n * 2; ++i)
            arr[i] = nums[i % n];

        long long cur = 0;
        int l = 0, x = INT_MAX;
        for (int i = 0; i < n * 2; ++i) {
            cur += arr[i];
            while (cur > target) {
                cur -= arr[l++];
            }
            if (cur == target)
                x = min(x, i - l + 1);
        }
        return x == INT_MAX ? -1 : x + ans;
    }
};