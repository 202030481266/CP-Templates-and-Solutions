// 应该是容斥原理
class Solution {
public:
    using ll = long long;
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size(); 
        ll f[1 << n];

        // 找到最小的数字，其中满足构造出来的数字>=k
        auto check = [&](ll hi) -> bool {
            memset(f, 0, sizeof(f));
            for (int i = 1; i < (1 << n); ++i) {
                int lc = 1;
                for (int j = 0; j < n; ++j) {
                    if ((i >> j) & 1) {
                        lc = lcm(lc, coins[j]);
                    }
                }
                f[i] = hi / lc;
            }
            ll sum = 0;
            for (int i = 1; i < (1 << n); ++i) {
                int b = __builtin_popcount(i);
                if (b & 1) sum += f[i];
                else sum -= f[i];
            }
            return sum >= k;
        };

        ll l = 0, r = 2e15; // (l, r]
        while (l + 1 < r) {
            ll mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }

};