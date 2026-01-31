#include <bits/stdc++.h>
using namespace std;

static constexpr int maxn = 1001;

int dp[maxn][maxn];

class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = 0;
            }
        }
        for (auto& d : dig) {
            dp[d[0]][d[1]] = 1;
        }
        int ans = 0;
        for (auto& a : artifacts) {
            int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
            bool flag = true;
            for (int i = x1; i <= x2; ++i) {
                for (int j = y1; j <= y2; ++j) {
                    if (dp[i][j] == 0) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) ++ans;
        }
        return ans;
    }
};