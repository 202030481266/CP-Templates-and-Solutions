class Solution {
public:
    using ll = long long;
    long long maxGcdSum(vector<int>& nums, int k) {
        // 暴力：维护一个前缀的GCD表
        int n = nums.size();
        unordered_map<int, int> pre;

        ll ans = 0;
        vector<ll> sum(n + 1);
        for (int i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + nums[i];
        for (int i = 0; i < n; ++i) {
            unordered_map<int, int> cur;
            for (auto [key, value] : pre) {
                int g = gcd(key, nums[i]);
                int index = value;
                if (pre.count(g)) index = min(index, pre[g]);
                if (i - index + 1 >= k) { // [value, i]
                    ans = max(ans, 1ll * (sum[i + 1] - sum[index]) * g); 
                }
                if (cur.count(g)) cur[g] = min(cur[g], index);
                else cur[g] = index;
            }
            // insert only one
            if (!cur.count(nums[i])) {
                cur[nums[i]] = i;// the most left one
                if (k == 1) ans = max(ans, 1ll * nums[i] * nums[i]);
            }
            pre = move(cur);
        }
        return ans;
    }
};