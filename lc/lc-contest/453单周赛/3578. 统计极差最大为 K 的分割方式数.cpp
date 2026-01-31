// https://leetcode.cn/problems/count-partitions-with-max-min-difference-at-most-k/description/
// 单调队列可以优化这个dp
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int mod = 1e9 + 7;

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        multiset<int> s;
        vector<int> dp(n + 1, 0);
        int l = 1;
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            s.insert(nums[i-1]);
            while (s.size() >= 2 && *s.rbegin() - *s.begin() > k) {
                s.erase(s.find(nums[l-1]));
                l++;
            }
            if (l == 1) dp[i] = dp[i-1];
            else dp[i] = (dp[i-1] - dp[l-2] + mod) % mod;
            dp[i] = (dp[i] + dp[i-1]) % mod;
            
        }
        return (dp[n] - dp[n-1] + mod) % mod;
    }
};