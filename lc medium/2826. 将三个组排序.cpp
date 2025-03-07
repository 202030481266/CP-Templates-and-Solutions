#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

// O(n) algorithm

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(3, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < 3; ++j) {
                dp[j] = min(dp[j], dp[j-1]);
            }
            for (int j = 0; j < 3; ++j) {
                if (nums[i] != j+1) {
                    dp[j]++;
                }
            }
        }
        return *min_element(dp.begin(), dp.end());
    }
};