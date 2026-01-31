#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dp[100010], a[100010];

class Solution {
public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        memset(a, 0, sizeof(a));
        int ans = 0;
        for (int v : nums) {
            int cnt = 1, tmp = 0;
            if (v-1 >= 0) {
                tmp = (tmp + dp[v-1]) % mod;
                cnt = (cnt + a[v-1]) % mod;
            }
            tmp = (tmp + dp[v+1]) % mod;
            cnt = (cnt + a[v+1]) % mod;
            dp[v] = ((dp[v] + tmp) % mod + 1ll * cnt * v % mod) % mod;
            a[v] = (a[v] + cnt) % mod;
        }
        int mx = *max_element(nums.begin(), nums.end());
        for (int i = 0; i <= mx; ++i) {
            ans = (ans + dp[i]) % mod;
        }
        return ans;
    }
};