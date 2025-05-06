#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

int sum[101];
int pos[55];
int dp[51][11][51];

class Solution {
public:
    int minTravelTime(int L, int n, int K, vector<int>& position, vector<int>& time) {
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + time[i];
            pos[i+1] = position[i];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= K; ++j) {
                for (int l = 0; l <= i; ++l) {
                    dp[i][j][l] = inf;
                }
            }
        }
        int ans = inf;
        dp[1][0][1] = 0;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j <= min(K, i-2);  ++j) {
                for (int l = 1; l <= j + 1; ++l) {
                    int l_merge = j - l + 1, l_pos = i - l;
                    if (l_pos > 0) {
                        for (int x = 1; x <= min(l_merge + 1, l_pos); ++x) {
                            if (dp[l_pos][l_merge][x] < inf) {
                                dp[i][j][l] = min(dp[i][j][l], dp[l_pos][l_merge][x] + 
                                    (sum[l_pos] - sum[l_pos - x]) * (pos[i] - pos[i-l]));
                            }
                        }
                    }
                }
            }
        }
        for (int i = 1; i <= min(K+1, n); ++i) ans = min(ans, dp[n][K][i]);
        return ans;
    }
};