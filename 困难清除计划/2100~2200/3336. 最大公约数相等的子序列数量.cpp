#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 还是DP，这个DP出现的频率真的是高
const int N = 205;
int dp[2][N][N];
int g[N][N];

bool init = false;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());         

        if (!init) {
            for (int i = 0; i <= 200; ++i)
                for (int j = 0; j <= 200; ++j)
                    g[i][j] = gcd(i, j);
            init = true;
        }

        memset(dp, 0, sizeof(dp));
        int pre = 0, cur = 1;
        dp[pre][0][0] = 1;
        for (int v : nums) {
            memcpy(dp[cur], dp[pre], sizeof(dp[pre]));
            for (int x = 0; x <= mx; ++x) {
                for (int y = 0; y <= mx; ++y) {
                    dp[cur][g[x][v]][y] = (dp[cur][g[x][v]][y] + dp[pre][x][y]) % mod;
                    dp[cur][x][g[y][v]] = (dp[cur][x][g[y][v]] + dp[pre][x][y]) % mod;
                }
            }
            cur ^= 1;
            pre ^= 1;
        }
        int ans = 0;
        for (int i = 1; i <= mx; ++i)
            ans = (ans + dp[pre][i][i]) % mod;
        return ans;
    }
};
