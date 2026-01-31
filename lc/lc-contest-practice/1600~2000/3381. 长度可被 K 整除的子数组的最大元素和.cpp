#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const ll inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> mn(k, inf);
        mn[0] = 0;
        ll cur = 0, ans = -inf;
        for (int i = 1; i <= n; ++i) {
            cur += nums[i-1];
            int r = i % k;
            if (mn[r] != inf) {
                ans = max(ans, cur - mn[r]);
            }
            mn[r] = min(mn[r], cur);
        }
        return ans;
    }
};