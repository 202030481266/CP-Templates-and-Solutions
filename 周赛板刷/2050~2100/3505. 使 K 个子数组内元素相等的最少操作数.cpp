#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        multiset<int> mn, mx;
        vector dp(n + 1, vector<ll>(k + 1, llinf));
        for (int i = 0; i <= n; ++i) dp[i][0] = 0;
        ll mn_sum = 0, mx_sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mn.empty()) {
                mn.insert(nums[i]);
                mn_sum += nums[i];
            }
            else {
                if (nums[i] > *mn.rbegin()) {
                    mx.insert(nums[i]);
                    mx_sum += nums[i];
                    while (mx.size() > mn.size()) {
                        mn.insert(*mx.begin());
                        mn_sum += *mx.begin();
                        mx_sum -= *mx.begin();
                        mx.erase(mx.begin());
                    }
                }
                else {
                    mn.insert(nums[i]);
                    mn_sum += nums[i];
                    while (mn.size() > mx.size() + 1) {
                        mx.insert(*mn.rbegin());
                        mx_sum += *mn.rbegin();
                        mn_sum -= *mn.rbegin();
                        mn.erase(--mn.end());
                    }
                }
            }
            if (i >= x) {
                if (mn.find(nums[i-x]) != mn.end()) {
                    mn.erase(mn.find(nums[i-x]));
                    mn_sum -= nums[i-x];
                    while (mn.size() < mx.size()) {
                        mn.insert(*mx.begin());
                        mn_sum += *mx.begin();
                        mx_sum -= *mx.begin();
                        mx.erase(mx.begin());
                    }
                }
                else {
                    mx.erase(mx.find(nums[i-x]));
                    mx_sum -= nums[i-x];
                    while (mn.size() > mx.size() + 1) {
                        mx.insert(*mn.rbegin());
                        mx_sum += *mn.rbegin();
                        mn_sum -= *mn.rbegin();
                        mn.erase(--mn.end());
                    }
                }
            }
            if (i >= x - 1) {
                ll mid = *mn.rbegin();
                ll cost = mid * (ll)mn.size() - mn_sum + mx_sum - mid * (ll)mx.size();
                for (int j = 1; j <= k; ++j) {
                    dp[i+1][j] = dp[i][j];
                    if (dp[i-x+1][j-1] != llinf) {
                        dp[i+1][j] = min(dp[i+1][j], dp[i-x+1][j-1] + cost);
                    }
                }
            }
        }
        ll ans = llinf;
        for (int i = 1; i <= n; ++i) ans = min(ans, dp[i][k]);
        return ans;
    }
};