#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int buildWall(int height, int width, vector<int>& bricks) {
        // 状态压缩dp
        int w=width-1;
        vector f(width, vector<int>(1<<w));
        for (int i = 0; i < width; ++i) {
            for (int v : bricks) {
                if (v <= i+1) {
                    int pos = i-v;
                    if (pos<0) f[i][0] += 1; // v==i+1
                    else {
                        for (int pre = 0; pre < (1<<pos); ++pre) {
                            f[i][pre|(1<<pos)] += f[pos][pre];
                            f[i][pre|(1<<pos)] %= mod;
                        }
                    }
                }
            }
        }
        // dp[i][s] = dp[i-1][x] if s & x == 0
        vector dp(height, vector<int>(1<<w));
        dp[0] = f[width-1];
        for (int i = 1; i < height; ++i) {
            for (int s = 0; s < (1<<w); ++s)
                for (int x = 0; x < (1<<w); ++x)
                    if ((s & x) == 0) dp[i][s] = (dp[i][s] + (f[width-1][s] * dp[i-1][x]) % mod) % mod;
        }
        int ans = 0;
        for (int i = 0; i < (1<<w); ++i)
            ans = (ans + dp[height-1][i]) % mod;
        return ans;
    }
};