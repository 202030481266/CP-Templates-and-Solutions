#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int j = 0, ans = inf;
        for (int i = 0; i < n; ++i) {
            while (j < n && nums[j] <= 1ll * nums[i] * k) ++j;
            ans = min(ans, i + n - j);
        }
        return ans;
    }
};