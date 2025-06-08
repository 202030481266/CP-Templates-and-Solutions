// https://leetcode.cn/problems/maximize-subarray-gcd-score/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int mod = 1e9 + 7;

class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        ll ans = 0;
        int n = nums.size();
        vector cnt(n, vector<int>(31));
        vector<int> gcds(n);
        for (int i = 0; i < n; ++i) {
            int x = nums[i], p = 0;
            while (x % 2 == 0) {
                ++p;
                x /= 2;
            }
            for (int j = 0; j <= 30; ++j) {
                cnt[i][j] = (i == 0 ? 0 : cnt[i - 1][j]);
            }
            cnt[i][p]++;
        }
        for (int i = 0; i < n; ++i) {
            gcds[i] = nums[i];
            for (int j = i - 1; j >= 0; --j) {
                gcds[j] = gcd(gcds[j + 1], nums[j]);
            }
            for (int j = 0; j <= i; ++j) {
                int p = 0, x = gcds[j];
                while (x % 2 == 0) {
                    p++;
                    x /= 2;
                }
                ans = max(ans, 1ll * gcds[j] * (i - j + 1));
                // (p, 30], [j, i]
                int need = (j == 0 ? cnt[i][p] : cnt[i][p] - cnt[j-1][p]);
                if (k >= need) {
                    ans = max(ans, 1ll * gcds[j] * (i - j + 1) * 2);
                }
            }
        }
        return ans;
    }
};