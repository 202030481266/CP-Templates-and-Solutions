// https://leetcode.cn/problems/count-the-number-of-computer-unlocking-permutations/description/

using ll = long long;

static constexpr int mod = 1e9 + 7;

class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        int n = complexity.size();   
        for (int i = 1; i < n; ++i) {
            if (complexity[i] <= complexity[0]) return 0;
        }
        int ans = 1;
        for (int i = 1; i <= n - 1; ++i) {
            ans = 1ll * ans * i % mod;
        }
        return ans;
    }
};
