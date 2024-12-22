#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = -inf;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            l = max(l, nums[i]-k);
            if (l <= nums[i]+k) {
                ++ans;
                ++l;
            }
        }
        return ans;
    }
};