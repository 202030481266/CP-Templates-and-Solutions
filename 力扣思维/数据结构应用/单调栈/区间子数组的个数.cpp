// https://leetcode.cn/problems/number-of-subarrays-with-bounded-maximum/
// 寻找子数组中最大值的在[left, right]的个数
// 可以使用单调栈来做，但是明显使用分类讨论更简单
// 可以使用双指针来表示，但是数组更简单

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size();
        vector<int> a(n);
        vector<int> b(n);

        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > right) cur = i + 1;
            else a[i] = cur;
        }
        cur = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] >= left && nums[i] <= right) {
                b[i] = i;
                cur = i;
            } else b[i] = cur;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > right) continue;
            else if (nums[i] >= left) {
                ans += (i - a[i] + 1);
            } else {
                if (b[i] < a[i]) continue;
                ans += (b[i] - a[b[i]] + 1);
            }
        }
        return ans;
    }
};