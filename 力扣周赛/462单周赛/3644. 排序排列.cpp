#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 这题非常有意思，类似于二进制中的gcd

class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n && i == nums[i]) ++i;
        if (i == n) return 0;
        int ans = i & nums[i];
        while (i < n) {
            if (i != nums[i]) ans &= nums[i];
            ++i;
        }
        return ans;
    }
};