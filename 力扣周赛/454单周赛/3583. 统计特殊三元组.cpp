// https://leetcode.cn/problems/count-special-triplets/description/
using ll = long long;

static constexpr int mod = 1e9 + 7;
int cnt[100005], lcnt[100005];

class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        for (int v : nums) cnt[v] = lcnt[v] = 0;
        for (int v : nums) if (v * 2 <= mx) cnt[v * 2] = lcnt[v * 2] = 0;
        for (int v : nums) ++cnt[v];
        lcnt[nums[0]] = 1;
        --cnt[nums[0]];
        ll ans = 0;
        for (int i = 1; i < n - 1; ++i) {
            --cnt[nums[i]];
            if (nums[i] * 2 <= mx) {
                ans = (ans + 1ll * lcnt[nums[i] * 2] * cnt[nums[i] * 2]) % mod;
            }
            ++lcnt[nums[i]];
        }
        return ans;
    }
};
