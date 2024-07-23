#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) 
            nums[i] = target[i] - nums[i];
        int p = (nums[0] == 0 ? 0 : (nums[0] > 0 ? 1 : -1));
        ll ans = abs(nums[0]), mx = ans;
        for (int i = 1; i < n; ++i) {
            if (nums[i] == 0) {
                if (p != 0) {
                    mx = 0;
                    p = 0;
                }
            } else if (nums[i] * p > 0) {
                if (abs(nums[i]) > mx) {
                    ans += abs(nums[i]) - mx;
                }
                mx = abs(nums[i]);
            } else {
                mx = abs(nums[i]);
                ans += mx;
                p = nums[i] > 0 ? 1 : -1;
            }
        }
        return ans;
    }
};