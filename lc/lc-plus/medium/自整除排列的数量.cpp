#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int selfDivisiblePermutationCount(int n) {
        vector<int> dp(1<<n);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int s = (1<<n)-1; s > 0; --s) {
                for (int j = 0; j < n; ++j) {
                    if (((s>>j) & 1)&&(gcd(j+1,i)==1)) {
                        dp[s] += dp[s^(1<<j)];
                    }
                }
            }
        }
        return dp[(1<<n)-1];
    }
};