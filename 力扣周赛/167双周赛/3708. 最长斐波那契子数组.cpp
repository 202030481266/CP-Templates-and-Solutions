#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int ans = 2, n = nums.size();
        int p = 0;
        while (p < n) {
            int i = p + 1;
            if (i < n) {
                while (i + 1 < n && nums[i + 1] == nums[i] + nums[i - 1]) ++i;
                ans = max(ans, i - p + 1);
                p = i;
            }
            else ++p;
        }
        return ans;
    }
};