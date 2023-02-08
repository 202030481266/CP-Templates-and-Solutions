// https://leetcode.cn/problems/container-with-most-water/description/
// 技巧双指针和贪心分析（短板瓶颈效应）

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n - 1;

        int ans = 0;
        while (left < right) {
            if (height[left] > height[right]) ans = max(ans, height[right] * (right - left)), right--;
            else ans = max(ans, height[left] * (right - left)), left++;
        }
        return ans;
    }
};