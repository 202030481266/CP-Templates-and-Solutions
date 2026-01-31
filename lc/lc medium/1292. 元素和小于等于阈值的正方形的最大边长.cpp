#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int n = mat.size(), m = mat[0].size();
        vector sum(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + mat[i][j];
            }
        }
        
        auto check = [&](int len) -> bool {
            for (int i = 1; i + len - 1 <= n; ++i) {
                for (int j = 1; j + len - 1 <= m; ++j) {
                    if (sum[i + len - 1][j + len - 1] - sum[i - 1][j + len - 1] - sum[i + len - 1][j - 1] + sum[i - 1][j - 1] <= threshold)
                        return true;
                }
            }
            return false;
        };
        
        int l = 0, r = min(n, m) + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }
        return l;
    }
};