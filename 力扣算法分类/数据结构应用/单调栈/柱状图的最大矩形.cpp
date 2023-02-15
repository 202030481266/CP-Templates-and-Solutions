// https://leetcode.cn/problems/largest-rectangle-in-histogram/
// 经典单调栈题目,对于每一个矩形而言可以看成是柱子往两边的扩展，其中的高度取决于柱子的高度
// 那么可以枚举每一个柱子，它能够得到的最大扩展取决于左边第一个小于它的元素和右边第一个小于它的元素
// 单调栈维护，升序，栈内每一个元素表示的是左边第一个比自己小的元素

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 哨兵技巧
        heights.push_back(0);
        heights.insert(heights.begin(), 0);
        stack<int> s;
        s.push(0);
        int ans = 0, n = heights.size();
        for (int i = 1; i < n; ++i) {
            while (!s.empty() && heights[s.top()] > heights[i]) {
                int u = s.top();
                s.pop();
                // i - 1 ~ s.top() + 1是满足要求heights >= heights[u]的柱子坐标
                int w = (i - 1) - (s.top() + 1) + 1;
                ans = max(ans, heights[u] * w);
            }
            s.push(i);
        }
        return ans;
    }
};