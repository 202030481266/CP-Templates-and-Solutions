#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();
        int x = 0, y = n - 1;
        while (x + 1 < n && nums[x + 1] > nums[x]) ++x;
        while (y - 1 >= 0 && nums[y - 1] > nums[y]) --y;
        if (y - x > 1) return -1;
        ll s1 = 0, s2 = 0;
        if (x == y) {
            for (int i = 0; i < x; ++i) s1 += nums[i];
            for (int i = x + 1; i < n; ++i) s2 += nums[i];
            return min(abs(s1 + nums[x] - s2), abs(s1 - nums[x] - s2));
        }
        for (int i = 0; i <= x; ++i) s1 += nums[i];
        for (int i = y; i < n; ++i) s2 += nums[i];
        return abs(s1 - s2);
    }
};