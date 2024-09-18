#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

class Solution {
public:
    int minLargest(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vi> dp(n+1, vi(m+1, INF));
        dp[0][0] = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                int tmp = INF;
                // 1 1 +2, 1 0 +1, 0 1 +1, 0 0 +2
                if (i > 0) {
                    tmp = min(tmp, dp[i-1][j] + ((nums1[i-1] ^ (dp[i-1][j] & 1)) ? 1 : 2));
                }
                if (j > 0) {
                    tmp = min(tmp, dp[i][j-1] + ((nums2[j-1] ^ (dp[i][j-1] & 1)) ? 1 : 2));
                }
                dp[i][j] = min(dp[i][j], tmp);
            }
        }
        return dp[n][m];
    }
};