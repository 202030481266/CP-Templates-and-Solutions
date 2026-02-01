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


class Solution {
public:
    int longestAlternating(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        auto check = [&](int a, int b, int c) -> int {
            if (a < b && b > c) return 1;
            if (a > b && b < c) return 2;
            return 0;
        };
        for (int i = 0; i < n; ++i) {
            pre[i] = i > 0 && nums[i] != nums[i - 1] ? 2 : 1;
            if (i > 1) {
                int t = check(nums[i - 2], nums[i - 1], nums[i]);
                if (t > 0) pre[i] = pre[i - 1] + 1;
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = i < n - 1 && nums[i] != nums[i + 1] ? 2 : 1;
            if (i < n - 2) {
                int t = check(nums[i], nums[i + 1], nums[i + 2]);
                if (t > 0) suf[i] = suf[i + 1] + 1;
            }
        }
        int ans = *ranges::max_element(pre);
        if (n <= 2) return ans;
        for (int i = 1; i < n - 1; ++i) {
            int t = check(nums[i - 1], nums[i], nums[i + 1]);
            if (!t && nums[i + 1] != nums[i - 1]) {
                if (i == 1 && i == n - 2) ans = max(ans, 2);
                else if (i == 1) ans = max(ans, check(nums[i - 1], nums[i + 1], nums[i + 2]) > 0 ? pre[i - 1] + suf[i + 1] : 2);
                else if (i == n - 2) ans = max(ans, check(nums[i - 2], nums[i - 1], nums[i + 1]) > 0 ? pre[i - 1] + suf[i + 1] : 2);
                else {
                    int x = check(nums[i - 1], nums[i + 1], nums[i + 2]);
                    int y = check(nums[i - 2], nums[i - 1], nums[i + 1]);
                    if (x && y) ans = max(ans, pre[i - 1] + suf[i + 1]);
                    else if (x) ans = max(ans, suf[i + 1] + 1);
                    else if (y) ans = max(ans, pre[i - 1] + 1);
                    else ans = max(ans, 2);
                }
            }
        }
        return ans;
    }
};
