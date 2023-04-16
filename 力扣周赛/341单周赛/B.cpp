class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        int n = nums.size(), res = -1, ans = -1;
        for (int v : divisors) {
            int tmp = 0;
            for (int u : nums) if (u % v == 0) ++tmp;
            if (tmp > res || (tmp == res && v < ans)) res = tmp, ans = v;
        }
        return ans;
    }
};