#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        int a = y, b = x;
        // a->b
        if (a >= b) return a-b;
        vector<int> dp(b+1, inf);
        dp[a]=0;
        queue<int> q;
        q.push(a);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u-1 > 0 && dp[u-1]>dp[u]+1) {
                dp[u-1]=dp[u]+1;
                q.push(u-1);
            }
            if (u+1 <= b) {
                if (dp[u+1]>dp[u]+1) {
                    dp[u+1] = dp[u]+1;
                    q.push(u+1);
                }
            }
            if (u*5 <= b) {
                if (dp[u*5]>dp[u]+1) {
                    dp[u*5]=dp[u]+1;
                    q.push(u*5);
                }
            }
            else dp[b]=min(dp[b], dp[u]+1+5*u-b);
            if (u*11 <= b) {
                if (dp[11*u]>dp[u]+1) {
                    dp[u*11]=dp[u]+1;
                    q.push(u*11);
                }
            }
            else dp[b]=min(dp[b], dp[u]+1+u*11-b);
        }
        return dp[b];
    }
};