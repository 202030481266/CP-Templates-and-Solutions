#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 想了半天 状压dp ，发现很难有一个合适的子结构
// 爆搜似乎是一个唯一解法（最小的覆盖集）

class Solution {
public:
    int removeOnes(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans += grid[i][j];
            }
        }
        auto a = grid;
        function<void(int, int)> dfs = [&](int res, int sum) {
            if (res > ans) return;
            if (sum == 0) {
                ans = res;
                return;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (a[i][j]) {
                        int tmp = 0, row = 0, col = 0;
                        for (int k = 0; k < n; ++k) {
                            if (a[k][j]) {
                                a[k][j] = 0;
                                col |= (1<<k);
                                ++tmp;
                            }
                        }
                        for (int k = 0; k < m; ++k) {
                            if (a[i][k]) {
                                a[i][k] = 0;
                                row |= (1<<k);
                                ++tmp;
                            }
                        }
                        dfs(res + 1, sum - tmp);
                        // backtrace
                        for (int k = 0; k < n; ++k) {
                            if ((col>>k)&1) {
                                a[k][j] = 1;
                            }
                        }
                        for (int k = 0; k < m; ++k) {
                            if ((row>>k)&1) {
                                a[i][k] = 1;
                            }
                        }
                    }
                }
            }
        };
        dfs(0, ans);
        return ans;
    }
};