#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int n = grid.size(), m = grid[0].size();
        vector tmp(n, vector<int>(m));
        for (int i = x; i < x + k; ++i) {
            for (int j = y; j < y + k; ++j) {
                tmp[i][j] = grid[2 * x + k - 1 - i][j];
            }
        }
        for (int i = x; i < x + k; ++i) {
            for (int j = y; j < y + k; ++j) {
                grid[i][j] = tmp[i][j];
            }
        }
        return grid;
    }
};