#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int n = source.size(), m = pattern.size(), N = targetIndices.size();
        vector<int> dp(N+1, -inf); // dp[i][j]
        vector<int> a(n+1);
        for (int& v : targetIndices) a[v+1] = 1;
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (!a[i]) {
                for (int j = 0; j <= min(N, i); ++j) {
                    // not take
                    if (dp[j] != -inf && dp[j] < m && pattern[dp[j]] == source[i-1]) 
                        dp[j]++;
                }
            }
            else {
                for (int j = min(N,i); j >= 0; --j) {
                    int tmp = (j > 0 ? max(dp[j-1], dp[j]) : dp[j]); // take
                    // not take
                    if (dp[j] != -inf && dp[j] < m && pattern[dp[j]] == source[i-1]) 
                        tmp = max(tmp, dp[j]+1);
                    dp[j] = tmp;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= N; ++i) {
            if (dp[i] == m) ans = i;
        }
        return ans;
    }
};