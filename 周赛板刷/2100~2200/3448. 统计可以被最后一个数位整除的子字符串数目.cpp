#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

ll dp[2][10];

class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.size();
        ll ans = 0;
        for (int i = 1; i < 10; ++i) {
            memset(dp, 0, sizeof(dp));
            int pre = 0, cur = 1;
            for (int j = 0; j < n; ++j) {
                memset(dp[cur], 0, sizeof(dp[cur]));
                int num = (s[j] - '0') % i;
                dp[cur][num] = 1;
                for (int k = 0; k < i; ++k) {
                    if (dp[pre][k]) {
                        // (k * 10 + num) % i
                        // (k % i) * 10 % i + num % i
                        int nxt = (k * 10 % i + num) % i;
                        dp[cur][nxt] += dp[pre][k]; 
                    }
                }
                if (s[j] - '0' == i) {
                    ans += dp[cur][0];
                }
                swap(pre, cur);
            }
        }
        return ans;
    }
};