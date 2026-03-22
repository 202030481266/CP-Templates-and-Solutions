#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int dp[2][1 << 14];

class Solution {
public:
    int minRemovals(vector<int>& nums, int target) {
        // A ^ B = target, A = B ^ target
        int n = nums.size();
        int c = 0;
        for (int v : nums) c ^= v;
        c ^= target;
        memset(dp[0], 0x3f, sizeof(dp[0]));
        int pre = 0, cur = 1;
        dp[0][0] = 0;
        for (int v : nums) {
            memset(dp[cur], 0x3f, sizeof(dp[cur]));
            for (int i = 0; i < 1 << 14; ++i) {
                dp[cur][i] = dp[pre][i];
                if (dp[pre][i ^ v] + 1 < dp[cur][i]) dp[cur][i] = dp[pre][i ^ v] + 1;
            }
            swap(pre, cur);
        }
        return dp[pre][c] == INF ? -1 : dp[pre][c];
    }
};