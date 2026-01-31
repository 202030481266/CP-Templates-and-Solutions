#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int maximumTripletValue(vector<int>& nums) {
        // 维护一个右边的最大数组，右边无脑选最大就行了，左边需要维护一个set
        int n = nums.size(), ans = 0;
        vector<int> mx(n);
        set<int> s{nums[0]};
        mx[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; --i) mx[i] = max(mx[i+1], nums[i]);
        for (int i = 1; i < n-1; ++i) {
            auto it = s.lower_bound(nums[i]);
            if (it != s.begin() && nums[i] < mx[i+1]) {
                it = prev(it);
                ans = max(ans, *it + mx[i+1] - nums[i]);
            }
            s.insert(nums[i]);
        }
        return ans;
    }
};