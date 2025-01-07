#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(k+1, vector<int>(n+1, 0));
        int m = 0;
        while (dp[k][m] < n) {
            m++;
            for (int i = 1; i <= k; i++)
                dp[i][m] = dp[i][m-1] + dp[i-1][m-1] + 1;
        }
        return m;
    }
    int twoEggDrop(int n) {
        return superEggDrop(2, n);
    }
};