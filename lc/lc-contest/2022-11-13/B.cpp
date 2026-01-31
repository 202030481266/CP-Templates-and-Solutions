class Solution {
public:
    int lcm(int x, int y) {
        int g = __gcd(x, y);
        return g * (x / g) * (y / g);
    }
    int subarrayLCM(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int res = 1;
            for (int j = i; j < n; j++) {
                res = lcm(res, nums[j]);
                if (k % res) break;
                if (k == res) ++ans;
            }
        }
        return ans;
    }
};