class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int tmp = numsDivide[0];
        for (int i = 1; i < numsDivide.size(); ++i)
            tmp = __gcd(tmp, numsDivide[i]);
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int& v : nums) {
            if (tmp % v == 0) break;
            else ++ans;
        }
        return (ans == nums.size() ? -1 : ans);
    }
};