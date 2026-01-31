#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        int n = arr.size(), dp[target+1][4];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = target; j >= arr[i-1]; --j) {
                for (int k = 3; k >= 1; --k) {
                    dp[j][k] = (dp[j][k] + dp[j - arr[i-1]][k - 1]) % mod;
                }
            }
        }
        return dp[target][3];
    }
};