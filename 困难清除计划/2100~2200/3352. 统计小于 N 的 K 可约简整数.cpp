#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int countKReducibleNumbers(string s, int k) {
        int n = s.size(), dp[n][n];
        
        vector<int> f(n+1);
        f[1] = 0;
        for (int i = 2; i <= n; ++i) {
            int b = __builtin_popcount(i);
            f[i] = f[b] + 1;
        }

        memset(dp, -1, sizeof(dp));
        function<int(int, int, bool, bool)> dfs = [&](int p, int val, bool is_limit, bool is_num) -> int {
            if (p==n) {
                return is_num && 1+f[val] <= k && val > 0 ? 1 : 0;
            }
            if (!is_limit && is_num && dp[p][val] != -1) return dp[p][val];
            int res = 0;
            if (!is_num) {
                res = (res + dfs(p+1, val, false, false)) % mod;
                // should be 1
                res = (res + dfs(p+1, 1, is_limit && s[p] == '1', true)) % mod;
            }
            else {
                res = (res + dfs(p+1, val, is_limit && s[p] == '0', true)) % mod;
                if (!is_limit || s[p] == '1')
                    res = (res + dfs(p+1, val+1, is_limit && s[p] == '1', true)) % mod;
            }
            if (!is_limit && is_num) dp[p][val] = res;
            return res;
        };

        int ans = dfs(0, 0, true, false);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') ++res;
        }
        if (1+f[res] <= k) --ans;

        return ans;
    }
};