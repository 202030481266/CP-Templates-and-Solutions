typedef long long ll;
class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        // 1 <= n <= 40;
        // 折半搜索模板题目
        set<ll> f;
        for (int i = 0; i < (1 << n / 2); ++i) {
            ll t = 0;
            for (int j = 0; j < (n / 2); ++j) 
                if ((i >> j) & 1) t += nums[j];
            f.emplace(t);
        }
        ll ans = 2e10, g = goal;
        for (int i = 0; i < (1 << (n - n / 2)); ++i) {
            ll t = 0;
            for (int j = 0; j < (n - n / 2); ++j)
                if ((i >> j) & 1) t += nums[n / 2 + j];
            ans = min(ans, abs(g - t));
            auto it = f.lower_bound(g - t);
            if (it != f.end()) {
                ans = min(ans, t - g + *it);
            }
            if (it != f.begin()) {
                ans = min(ans, g - (t + *prev(it)));
            }
        }
        return ans;
    }
};