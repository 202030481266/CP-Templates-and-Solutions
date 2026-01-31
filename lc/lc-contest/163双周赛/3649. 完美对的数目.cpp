#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;



class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        int n = nums.size();
        for (int& v : nums) v = abs(v);
        ranges::sort(nums);
        int l = 0, r = 0; 
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            while (r < n && nums[r] <= nums[i] * 2) ++r;
            while (nums[l] < (nums[i] + 1) / 2) ++l;
            // [l, r)
            ans += r - l - 1; // 减去自己
        }
        return ans / 2;
    }
};