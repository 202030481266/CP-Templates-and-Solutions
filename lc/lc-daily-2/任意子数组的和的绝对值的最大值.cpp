class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size(), mx = 0, mn = 0, sum = 0;
        int ans = 0;
        for (int& c : nums) {
            sum += c;
            ans = max(ans, abs(sum - mx));
            ans = max(ans, abs(sum - mn));
            mx = max(mx, sum);
            mn = min(mn, sum);
        }
        return ans;
    }
};