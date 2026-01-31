class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int pos = 0, neg = 0;
        for (auto c : nums) {
            if (c > 0) pos++;
            if (c < 0) neg++;
        }
        return max(pos, neg);
    }
};