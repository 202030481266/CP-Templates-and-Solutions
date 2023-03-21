class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        vector<int> a;
        vector<int> exi(value);
        for (auto c : nums) a.emplace_back(c % value);
        for (auto &c : a) {
            c = (c + value) % value;
            ++exi[c];
        }
        int n = nums.size();
        for (int t = 0; t < n; ++t) {
            for (int i = 0; i < value; ++i) {
                if (exi[i] == 0) return t * value + i;
                --exi[i];
            }
        }
        return n;
    }
};