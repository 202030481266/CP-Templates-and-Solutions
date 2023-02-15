// https://leetcode.cn/problems/trapping-rain-water/
// 经典单调栈题目，对于当前的柱子来说能够乘的水是由最左边不大于自己高度的柱子决定的
// 因此使用单调栈来维护这么一个序列，能够O(1)查询左边第一个大于自己高度的柱子就可以了
// 一边弹出元素，一边计算雨水的体积


class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};

