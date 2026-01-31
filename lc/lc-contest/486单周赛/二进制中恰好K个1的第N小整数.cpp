#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


ll dp[52][55][2];

class Solution {
public:
    long long nthSmallest(long long n, int k) {
        ll l = 0, r = 1LL << 50;
        auto check = [&](ll m) -> bool {
            int w = bit_width(1ULL * m);
            for (int i = 0; i < w; ++i) {
                for (int j = 0; j <= k; ++j) dp[i][j][0] = dp[i][j][1] = 0;
            }
            dp[0][0][0] = dp[0][0][1] = 1;
            dp[0][1][0] = 1;
            dp[0][1][1] = m & 1;
            for (int i = 1; i < w; ++i) {
                for (int j = 0; j <= min(k, i + 1); ++j) {
                    if (m >> i & 1) {
                        dp[i][j][0] += dp[i - 1][j][0] + (j > 0 ? dp[i - 1][j - 1][0] : 0);
                        dp[i][j][1] += dp[i - 1][j][0] + (j > 0 ? dp[i - 1][j - 1][1] : 0);
                    }
                    else {
                        dp[i][j][0] += dp[i - 1][j][0] + (j > 0 ? dp[i - 1][j - 1][0] : 0);
                        dp[i][j][1] = dp[i - 1][j][1];
                    }
                }
            }
            return dp[w - 1][k][1] >= n;
        };
        while (l + 1 < r) {
            ll mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};
