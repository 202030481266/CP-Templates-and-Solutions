class Solution {
public:
    int differenceOfSum(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        auto f = [&](int k) {
            vector<int> a;
            while (k) {
                a.emplace_back(k % 10);
                k /= 10;
            }
            return accumulate(a.begin(), a.end(), 0);
        };
        int ans = 0;
        for (auto c : nums) ans += f(c);
        return abs(ans - sum);
    }
};