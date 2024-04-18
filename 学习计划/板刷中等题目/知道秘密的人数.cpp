const int mod = 1e9 + 7;
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        // [1..n]
        vector<int> cnt(n+2);
        vector<int> f(n+2);

        auto add = [&](int l, int r, int val) {
            // add [l, r)
            cnt[l] = (cnt[l] + val) % mod;
            cnt[r] = (cnt[r] - val + mod) % mod;
        };

        int sum = 0, cur = 0;
        add(1, 2, 1);
        for (int i = 1; i <= n; ++i) {
            sum = (sum + cnt[i]) % mod; // sum is a[i]，新的增加的人
            cur = (((cur + sum) % mod - f[i])%mod + mod) % mod;// 现在有多少人
            if (i + delay <= n) { // 否则没有意义
                // [l, r)
                int l = min(n , i + delay), r = min(n + 1, i+forget);
                add(l, r, sum);
                f[r] = (f[r] + sum) % mod;
            }
        }
        return cur % mod;
    }
};