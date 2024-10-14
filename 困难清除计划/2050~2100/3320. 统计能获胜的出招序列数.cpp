#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int countWinningSequences(string s) {
        int n = s.size(), dp[2][3][2*n+2];

        memset(dp, 0, sizeof(dp)); 
        // F, W, E
        // 0, 1, 2

        vector<int> win{2, 0, 1};
        vector<int> loss{1, 2, 0};
        vector<int> a(n);
        unordered_map<char, int> mp = {{'F', 0}, {'W', 1}, {'E', 2}};

        for (int i = 0; i < n; ++i) a[i] = mp[s[i]];
        int pre = 0, cur = 1;
        dp[pre][win[a[0]]][-1 + n] = dp[pre][loss[a[0]]][1 + n] = dp[pre][a[0]][0 + n] = 1;
        
        for (int i = 1; i < n; ++i) {
            memset(dp[cur], 0, sizeof(dp[cur]));
            for (int j = -i-1; j <= i+1; ++j) {
                dp[cur][a[i]][j + n] = (1LL * dp[pre][win[a[i]]][j + n] + dp[pre][loss[a[i]]][j + n]) % mod;
                dp[cur][win[a[i]]][j + n] = (1LL * dp[pre][a[i]][j + 1 + n] + dp[pre][loss[a[i]]][j + 1 + n]) % mod;
                if (j + n > 0)
                    dp[cur][loss[a[i]]][j + n] = (1LL * dp[pre][a[i]][j - 1 + n] + dp[pre][win[a[i]]][j - 1 + n]) % mod;
            }
            swap(cur, pre);
        }
        
        int ans = 0;
        for (int i = n+1; i <= n*2; ++i) {
            ans = (ans + dp[pre][0][i]) % mod;
            ans = (ans + dp[pre][1][i]) % mod;
            ans = (ans + dp[pre][2][i]) % mod;
        }
        return ans;
    }
};
