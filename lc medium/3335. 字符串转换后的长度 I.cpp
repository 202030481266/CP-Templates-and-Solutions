#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e5;
ll dp[26][maxn+1];

bool flag = 0;

void init() {
    for (int i = 0; i < 26; ++i) dp[i][0] = 1;
    for (int i = 1; i <= maxn; ++i) {
        for (int j = 0; j < 26; ++j) {
            // j + 1 -> (j + 1) % 26, dp[j][i] = dp[(j+1)%26][i-1]
            if (j==25) dp[j][i]=(dp[0][i-1]+dp[1][i-1])%mod;
            else dp[j][i]=dp[j+1][i-1];
        }
    }
}

class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        if (!flag) {
            flag = 1;
            init();
        }
        vector<ll> cnt(26);
        for (char c : s) {
            cnt[c-'a']++;
        }
        ll ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans = (ans + cnt[i]*dp[i][t] % mod) % mod;
        }
        return ans;
    }
};