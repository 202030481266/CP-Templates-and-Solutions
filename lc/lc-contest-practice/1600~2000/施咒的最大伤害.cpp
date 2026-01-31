#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        int n = power.size();
        ll dp[n], mx = 0, l = 0, ans = 0;
        memset(dp, 0, sizeof(dp));
        unordered_map<int, int> mp;
        for (int& v : power) mp[v] += 1;
        sort(power.begin(), power.end());
        power.erase(unique(power.begin(), power.end()), power.end());
        for (int i = 0; i < power.size(); ++i) {
            while (power[i] - power[l] > 2) {
                mx = max(mx, dp[l]);
                ++l;
            }    
            dp[i] = mx + 1ll*power[i]*mp[power[i]];
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};