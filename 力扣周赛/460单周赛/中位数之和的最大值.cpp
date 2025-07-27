#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long maximumMedianSum(vector<int>& nums) {
        ll ans = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size(), m = n / 3, r = n - 2;
        for (int i = 1; i <= m; ++i) {
            ans += nums[r];
            r -= 2;
        }
        return ans;
    }
};