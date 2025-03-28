#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size(), s = accumulate(nums.begin(), nums.end(), 0);
        int mn = inf;
        if (n & 1) {
            mn = *min_element(nums.begin(), nums.end());
        }
        else {
            for (int i = 0; i + 1 < n; ++i) {
                mn = min(mn, nums[i] + nums[i + 1]);
            }
        }
        return s - mn;
    }
};