#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

// 本质上只有两种可能的数组

class Solution {
public:
    vector<int> makeParityAlternating(vector<int>& nums) {
        int n = nums.size();
        vi c;
        int mx = -INF, mn = INF;
        for (int i = 0; i < n; ++i) {
            if ((nums[i] & 1) ^ (i & 1)) c.push_back(nums[i]);
            else {
                mx = max(mx, nums[i]);
                mn = min(mn, nums[i]);
            }
        }
        auto cal = [&]() -> int {
            if (c.empty()) return mx - mn;
            int mx_val = *ranges::max_element(c);
            int mn_val = *ranges::min_element(c);
            int ans = INT_MAX;
            if (c.size() > 1) {
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (i == 0 || j == 0) continue;
                        int x = max(mx, max(mx_val + i, mn_val + j));
                        int y = min(mn, min(mx_val + i, mn_val + j));
                        ans = min(ans, x - y);
                    }
                }
            }
            else {
                int v1 = max(mx, c[0] + 1) - min(mn, c[0] + 1);
                int v2 = max(mx, c[0] - 1) - min(mn, c[0] - 1);
                ans = min(v1, v2);
            }
            return ans;
        };
        int cost1 = c.size(), dis1 = cal();
        c.clear();
        mx = -INF;
        mn = INF;
        for (int i = 0; i < n; ++i) {
            if (((nums[i] & 1) ^ (i & 1)) == 0) c.push_back(nums[i]);
            else {
                mx = max(mx, nums[i]);
                mn = min(mn, nums[i]);
            }
        }
        int cost2 = c.size(), dis2 = cal();
        if (cost1 != cost2) {
            if (cost1 < cost2) return {cost1, dis1};
            return {cost2, dis2};
        }
        return {cost1, min(dis1, dis2)};
    }
};