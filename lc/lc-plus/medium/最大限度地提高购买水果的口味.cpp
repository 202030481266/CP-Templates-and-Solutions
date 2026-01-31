#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int dp[1001][6];

class Solution {
public:
    int maxTastiness(vector<int>& price, vector<int>& tastiness, int maxAmount, int maxCoupons) {
        // 背包 ？
        int n = price.size();
        memset(dp, 0, sizeof(dp));
        // dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-price[i]][k] + tastiness[i], dp[i-1][j-price[i]//2][k-1]+tastiness[i])
        // O(n*maxCoupons*maxAmount)
        for (int i = 0; i < n; ++i) {
            // price[i]
            for (int j = maxAmount; j >= price[i] / 2; --j) {
                for (int k = maxCoupons; k >= 0; --k) {
                    if (j >= price[i]) dp[j][k] = max(dp[j][k], dp[j-price[i]][k] + tastiness[i]);
                    if (k) dp[j][k] = max(dp[j][k], dp[j-price[i]/2][k-1] + tastiness[i]);
                }
                
            }
        }
        return dp[maxAmount][maxCoupons];
    }
};