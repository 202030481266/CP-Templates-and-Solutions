#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;


class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size(), dp[n+1];
        memset(dp, 0x3f, sizeof(dp));

        // dp[i] = dp[i-1] + costs[0];
        // if days[i] >= 7, dp[i] = dp[x] + cost[1]
        // if days[i] >= 30, dp[i] = dp[y] + cost[2]

        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i-1] + costs[0];
            int j = i-1;
            while (j > 0 && days[i-1]-days[j-1]+1 <= 7) --j;
            dp[i] = min(dp[i], dp[j] + costs[1]);
            while (j > 0 && days[i-1]-days[j-1]+1 <= 30) --j;
            dp[i] = min(dp[i], dp[j] + costs[2]);
        }

        return dp[n];
    }
};