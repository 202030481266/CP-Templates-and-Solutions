class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        // 位运算的技巧
        int ans = 0;
        for (int& v :nums) ans |= v;
        return ans;
    }
};