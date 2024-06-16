#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    long long maxScore(vector<int>& nums, int x) {
        ll odd = 0, even = 0, ans = 0;
        if (nums[0] & 1) odd = nums[0],even=nums[0]-x;
        else even = nums[0],odd=nums[0]-x;
        ans = max(odd, even);
        for (int i = 1; i < nums.size(); ++i) {
            int v = nums[i];
            if (v & 1) {
                odd = max(odd + v, even + v - x);
            }
            else {
                even = max(even + v, odd + v - x);
            }
            ans = max(ans, max(odd, even));
        }
        return ans;
    }
};