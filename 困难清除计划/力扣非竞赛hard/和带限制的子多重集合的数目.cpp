class Solution {
    static constexpr int mod = 1e9 + 7;
    int dp[20010], cnt[20010];
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        int n = nums.size(), sum = 0; 

        for (int& v : nums) {
            sum += v;
            ++cnt[v];
        }

        vector<int> a;
        for (int i = 1; i <= 20000; ++i)
            if (cnt[i]) a.push_back(i);

        // 多重背包
        // sum <= 20000, 不同种类的数字最多有多少种？ 
        // 假设每一种只有一个数字，那么最多的就是不会超过200个，也就是对于桶来说，不过超过 200 个桶，更新的次数不会超过200次
        // 同余分组
        dp[0] = cnt[0] + 1; // empty set
        // 这个方法对于 0 来说不行
        for (int i = 0; i < a.size(); ++i) {
            for (int W = sum, k = a[i]; W >= 0 && k; --W, --k) {
                int l = W / a[i] - 1, cur_len = 1, s = dp[W], rem = W % a[i];
                for (int cur = W; cur >= 0; cur -= a[i]) {
                    --cur_len;
                    s = (s - dp[cur] + mod) % mod;
                    int len = min(cnt[a[i]], cur / a[i]);
                    while (cur_len < len && l >= 0) {
                        s = (s + dp[l * a[i] + rem]) % mod;
                        --l;
                        ++cur_len;
                    }
                    dp[cur] = (dp[cur] + s) % mod;
                }
            }
        }
        int ans = 0;
        for (int i = l; i <= r; ++i) ans = (ans + dp[i]) % mod;
        return ans;
    }
};