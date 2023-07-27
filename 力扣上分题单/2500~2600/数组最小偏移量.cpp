class Solution {
    set<int> s;
public:
    int minimumDeviation(vector<int>& nums) {
        int n = nums.size(), ans = INT_MAX;
        // 就是一个简单的等价原则
        // 一个奇数的操作就可以等价于两种操作，要么没有，要么乘以2
        for (int& c : nums) {
            if (c & 1) s.emplace(c * 2);
            else s.emplace(c);
        }
        if (s.size() == 1) return 0;
        while (*s.rbegin() % 2 == 0) {
            int x = *s.rbegin();
            s.erase(x);
            s.emplace(x / 2);
            int res = *s.rbegin() - *s.begin();
            ans = min(ans, res);
        }
        return ans;
    }
};