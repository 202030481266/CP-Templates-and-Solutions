class Solution {
public:
    int totalSteps(vector<int>& nums) {
        // 问题等价于所有数字都会比左边第一个大于自己的数字消掉
        // 但是对于这道题而言可以同时进行删除，所以有更加好的解法，即对于i来说，i是在a[i]之间最大值被删除后自己才会被删除
        // 关键点就是在于如果前面存在一个比自己小的数字，那么自己一定会在它被删除后被删除
        // 所以考虑维护一个单调递减的栈
        stack<pair<int, int>> s;
        int n = nums.size(), t = 0;

        for (int i = 0; i < n; ++i) {
            t = 0;
            while (!s.empty() && s.top().first <= nums[i]) {
                t = max(t, s.top().second);
                s.pop();
            }
            // 只有左边有大于它的数字或者说要被删除的数字才加1
            if (!s.empty()) ++t;
            ans = max(t, ans);
            s.emplace(nums[i], t);
        }
        return ans;
    }
};