class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), g = nums[0];
        for (int i = 1; i < n; ++i) g = gcd(g, nums[i]);
        if (g != 1) return -1;
        int cnt = 0;
        for (int i = 0; i < n; ++i) 
            if (nums[i] == 1) ++cnt;
        if (cnt > 0) return n - cnt;
        // 将 nums[i] 或者 nums[i+1] 两者之一替换成它们的最大公约数
        for (int len = 2; len <= n; ++len) 
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1; 
                g = nums[i];
                for (int k = i + 1; k <= j; ++k) g = gcd(g, nums[k]);
                if (g == 1) return (len - 1) + n - 1;
            }
        return 2 * (n - 1);
    }
};