#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int makeArrayPositive(vector<int>& nums) {
        int n = nums.size();
        vector<ll> sum(n + 1, 0);
        int ans = 0, last = 0;
        // (last, i]
        ll mx = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + nums[i-1];
            if (i - last > 2) {
                if (sum[i] <= mx) {
                    ++ans;
                    sum[i] = 0;
                    last = i;
                    mx = 0;
                }
                else {
                    mx = max(mx, sum[i-2]);
                }
            }
        }
        return ans;
    }
};