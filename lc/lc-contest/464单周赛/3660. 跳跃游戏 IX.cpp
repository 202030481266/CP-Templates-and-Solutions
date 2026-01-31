#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        int mx = 0, mn = inf;
        vector<int> pre(n);
        vector<int> ans(n);
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[mx]) mx = i;
            pre[i] = mx;
        }
        int p = n - 1;
        while (p >= 0) {
            int x = pre[p];
            if (nums[x] <= mn) mx = nums[x];
            while (p >= x) {
                ans[p] = mx;
                mn = min(mn, nums[p]);
                --p;
            }
        }
        return ans;
    }
};