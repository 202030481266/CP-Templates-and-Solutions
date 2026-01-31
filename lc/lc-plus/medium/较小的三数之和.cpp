#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < n-1; ++i) {
            for (int j = 0; j < i; ++j){
                int r = target - nums[i] - nums[j];
                int p = lower_bound(nums.begin() + i + 1, nums.end(), r) - nums.begin();
                if (p > i+1) {
                    // [i+1, p)
                    ans += p-i-1;
                }
            }
        }
        return ans;
    }
};