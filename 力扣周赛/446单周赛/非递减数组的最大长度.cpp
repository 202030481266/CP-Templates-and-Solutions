#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        int n = nums.size();
        int ans = 1, last = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] >= last) {
                ++ans;
                last = nums[i];
            }
        }
        return ans;
    }
};