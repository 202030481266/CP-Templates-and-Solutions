class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int l = 0, r = n - 1, ans = 0, lmax = 0, rmax = 0; 
        // 双指针优化
        // 因为前后缀数组实际上就是只是用了一次
        while (l < r) {
            lmax = max(lmax, height[l]);
            rmax = max(rmax, height[r]);
            if (height[l] >= height[r]) {
                ans += rmax - height[r];
                --r;
            }
            else {
                ans += lmax - height[l];
                ++l;
            }
        }
        return ans;
    }
};