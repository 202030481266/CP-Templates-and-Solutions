#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1, ans = 0;
        ll left = 0, right = 0;
        while (l < r) {
            left = nums[l++];
            right = nums[r--];
            while (l <= r && left != right) {
                if (left < right) left += nums[l++];
                else right += nums[r--];
                ++ans;
            }
        }
        if (left != right) ++ans;
        return ans;
    }
};