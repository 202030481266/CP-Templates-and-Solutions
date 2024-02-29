class Solution {
    using ll = long long;

public:
    long long minimumCost(vector<int>& nums) {
        // 枚举回文数字就可以
        // 枚举量不大，也就是109998
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<ll> sum(n + 1);
        for (int i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + nums[i];

        string mn = to_string(nums[0]), mx = to_string(nums[n - 1]);
        int low_bit = mn.size(), high_bit = mx.size();

        ll ans = 2e15;
        
        auto f = [&](int val) -> ll {
            int p = lower_bound(nums.begin(), nums.end(), val) - nums.begin();
            // [0, p - 1], [p, n - 1]
            // [1, p], [p + 1, n]
            ll res = sum[n] - 2 * sum[p] - 1ll * n * val + 2ll * p * val;
            return res;
        };
        auto rev = [&](int val) -> int {
            int x = 0;
            while (val) {
                x = x * 10 + val % 10;
                val /= 10;
            }
            return x;
        };
        int flag = 1;
        vector<int> c{1, 10, 100, 1000, 10000, 100000};
        for (int len = max(1, low_bit - 1); flag && len <= min(9, high_bit + 1);
             ++len) {
            int l = len / 2; // flag 表示是否已经枚举到了超过 mx 的数字
            if (l == 0) {
                for (int i = 1; i <= 9; ++i) {
                    if (i >= nums[n - 1])
                        flag = 0;
                    ans = min(ans, f(i));
                }
            } else {
                if (len & 1) {
                    // 奇数长度
                    for (int i = c[l - 1]; i < c[l]; ++i) {
                        for (int j = 0; j < 10; ++j) { // 中间部分
                            int cur = i * c[l + 1] + j * c[l] + rev(i);
                            if (cur >= nums[n - 1])
                                flag = 0;
                            ans = min(ans, f(cur));
                        }
                    }
                } else {
                    for (int i = c[l - 1]; i < c[l]; ++i) {
                        int cur = i * c[l] + rev(i);
                        if (cur >= nums[n - 1])
                            flag = 0;
                        ans = min(ans, f(cur));
                    }
                }
            }
        }
        
        return ans;
    }
};