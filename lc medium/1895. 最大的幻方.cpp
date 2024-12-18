#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        
        // 二维前缀和
        vector<vector<int>> s(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }

        auto f = [&](int x1, int y1, int x2, int y2) {
            return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
        };

        auto check = [&](int k) -> bool {
            for (int i = 1; i + k - 1 <= n; ++i) {
                for (int j = 1; j + k - 1 <= m; ++j) {
                    // (i, j), (i + k - 1, j + k - 1), (i + k - 1, j), (i, j + k - 1)
                    // 四个方向的和相等
                    int sum = f(i, j, i + k - 1, j + k - 1);
                    if (sum % k != 0) continue;
                    int s = sum / k;
                    bool flag = true;
                    // 检查行和列
                    for (int x = i; x <= i + k - 1; ++x) {
                        if (f(x, j, x, j + k - 1) != s) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) continue;
                    for (int y = j; y <= j + k - 1; ++y) {
                        if (f(i, y, i + k - 1, y) != s) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) continue;
                    // 检查对角线
                    int cur = 0;
                    for (int x = i, y = j; x <= i + k - 1; ++x, ++y) {
                        cur += grid[x - 1][y - 1];
                    }
                    if (cur != s) continue;
                    cur = 0;
                    for (int x = i, y = j + k - 1; x <= i + k - 1; ++x, --y) {
                        cur += grid[x - 1][y - 1];
                    }
                    if (cur != s) continue;
                    return true;
                }
            }
            return false;
        };

        for (int k = min(n, m); k >= 2; --k) {
            if (check(k)) return k;
        }
        return 1;
    }
};