#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        vector<ll> a(n+1), b(n+2);
        for (int i = 0; i < n; ++i) {
            a[i+1] = a[i] + nums[i];
            b[i+1] = b[i] + cost[i];
        }
        vector<ll> dp(n+1, llinf); 
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] = min(dp[i], dp[j] + a[i] * (b[i] - b[j]) + k * (b[n] - b[j]));
            }
        }
        return dp[n];
    }
};