#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxv = 1e5 + 7;
int a[maxv], b[maxv];
ll row[maxv], col[maxv];
ll rs[maxv], cs[maxv];

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for (int i = 0; i < n; ++i) row[i] = 0;
        for (int i = 0; i < m; ++i) col[i] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                row[i] += grid[i][j];
                col[j] += grid[i][j];
            }
        }
        rs[0] = row[0];
        cs[0] = col[0];
        for (int i = 1; i < n; ++i) rs[i] = rs[i-1] + row[i];
        for (int i = 1; i < m; ++i) cs[i] = cs[i-1] + col[i];
        // 水平切割
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                b[grid[i][j]]++;
            }
        }
        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j < m; ++j) {
                a[grid[i][j]]++;
                b[grid[i][j]]--;
            }
            if (rs[i] == rs[n-1] - rs[i]) return true;
            ll sub = abs(rs[n-1] - 2 * rs[i]);
            if (sub >= maxv) continue;
            if (rs[i] > rs[n-1] - rs[i]) {
                if (a[sub] > 0) {
                    if (i == 0) {
                        if (grid[0][0] == sub || grid[0][m-1] == sub) return true;
                    }
                    else {
                        if (m > 1 || grid[0][0] == sub || grid[i][0] == sub) return true;
                    }
                }
            }
            else {
                if (b[sub] > 0) {
                    if (i+1 == n-1) {
                        if (grid[n-1][0] == sub || grid[n-1][m-1] == sub) return true;
                    }
                    else {
                        if (m > 1 || grid[i+1][0] == sub || grid[n-1][0] == sub) return true;
                    }
                }
            }
        }
        // 垂直切割
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                b[grid[i][j]] = 0;
                a[grid[i][j]] = 0;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                b[grid[i][j]]++;
            }
        }
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                a[grid[i][j]]++;
                b[grid[i][j]]--;
            }
            if (cs[j] == cs[m-1] - cs[j]) return true;
            ll sub = abs(cs[m-1] - 2 * cs[j]);
            if (sub >= maxv) continue;
            if (cs[j] > cs[m-1] - cs[j]) {
                if (a[sub] > 0) {
                    if (j == 0) {
                        if (grid[0][0] == sub || grid[n-1][0] == sub) return true;
                    }
                    else {
                        if (n > 1 || grid[0][0] == sub || grid[0][j] == sub) return true;
                    }
                }
            }
            else {
                if (b[sub] > 0) {
                    if (j+1 == m-1) {
                        if (grid[0][m-1] == sub || grid[n-1][m-1] == sub) return true;
                    }
                    else {
                        if (n > 1 || grid[0][j+1] == sub || grid[0][m-1] == sub) return true;
                    }
                }
            }
        }
        return false;
    }
};