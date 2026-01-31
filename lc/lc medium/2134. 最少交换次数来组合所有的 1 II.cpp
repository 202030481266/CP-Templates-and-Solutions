#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> sum(n + 1);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + nums[i];
        }
        int ans = inf;
        for (int i = 1; i <= n; ++i) {
            if (i < sum[n]) {
                int j = sum[n] - i;
                // [1, i] [n - j + 1, n]
                ans = min(ans, sum[n] - sum[i] - (sum[n] - sum[n - j]));
            }
            else {
                // (i - sum[n], i]
                ans = min(ans, sum[n] - (sum[i] - sum[i - sum[n]]));
            }
        }
        return ans;
    }
};