#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
class Solution {
public:
    using ll = long long;
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        int n = nums.size();// 数学
        // 找到最小的数字有几个
        int mn = INT_MAX, mx = INT_MIN;
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            mn = min(mn, nums[i]);
            mx = max(mx, nums[i]);
        }
        if (mx == mn) return 0;
        int c = 0;
        for (int i = 0; i < n; ++i)
            if (nums[i] == mn) ++c;
        if (2 * cost1 <= cost2) {
            // 全部使用cost1肯定是最优的
            return (1ll * mx * n - sum) * cost1 % mod;
        }
        if (n <= 2) {
            // 只有两个元素，直接返回
            return 1ll * (mx - mn) * cost1 % mod;
        }
        // 尽量多使用cost2肯定更优，但是因为有限定所以要考虑
        auto cal = [&](ll upper) -> ll {
            ll op = 0, r = 0;
            if (c == 1 && (upper - mn) >= (upper * (n-1) - sum + mn)) {
                op = upper * (n - 1) - sum + mn;
                r = (upper - mn) - (upper * (n-1) - sum + mn);
            }
            else {
                op = (upper * n - sum) / 2;
                r = (upper * n - sum) % 2 == 0 ? 0 : 1;
            }
            return op * cost2 + r * cost1;
        };

        ll M = (sum - 2 * mn) / (n - 2), res;
        if (M < mx || c > 1) {
            // 比数组最大值还要小，说明后面所有的计算方法相同，单调递增
            // 如果c > 1，同样也是越小越好
            return min(cal(mx), cal(mx+1)) % mod;
        }
        // 大于 M 肯定是越小越好
        res = min(cal(M+1), cal(M+2));
        ll ans = 0, k = 1ll * cost2 * (n - 1) + 1ll * cost1 * (2 - n);
        if (k == 0)  
            ans = min(1ll * (mn - sum) * cost2 + 1ll * (sum - 2 * mn) * cost1, res); 
        else if (k > 0) 
            ans = min(cal(mx), res);
        else ans = min(cal(M), res);
        return ans % mod;
    }
};

