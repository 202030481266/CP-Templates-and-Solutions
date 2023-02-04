class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;
        auto f = [&](int x) {
            vector<int> a;
            while (x) {
                a.emplace_back(x % 10);
                x /= 10;
            }
            for (int i = a.size() - 1; i >= 0; --i)
                ans.emplace_back(a[i]);
        };
        for (auto c : nums) f(c);
        return ans;
    }
};