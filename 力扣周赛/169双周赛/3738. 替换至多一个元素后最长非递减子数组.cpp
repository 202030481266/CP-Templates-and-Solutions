#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 1), g(n, 1);
        for (int i = 1; i < n; ++i) {
            if (nums[i] >= nums[i - 1]) f[i] += f[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] <= nums[i + 1]) g[i] += g[i + 1];
        }
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            if (i > 0) ans = max(ans, f[i - 1] + 1);
            if (i + 1 < n) ans = max(ans, g[i + 1] + 1);
            if (i > 0 && i + 1 < n && nums[i - 1] <= nums[i + 1]) ans = max(ans, f[i - 1] + 1 + g[i + 1]); 
        }
        return ans;
    }
};