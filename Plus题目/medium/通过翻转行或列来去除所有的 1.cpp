#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    bool removeOnes(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // n + m = 600
        // xor gauss
        // 行变换和列变换实际上可以分开
        // 因为从1的视角来看，所有的变换都是一样的
        // 并且对于每一个行或者列，实际上最多变换一次
        
        for (int i = 1; i < n; ++i) {
            bool ok1 = true, ok2 = true;
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != grid[0][j]) {
                    ok1 = false;
                    break;
                }
            }
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != (grid[0][j]^1)) {
                    ok2 = false;
                    break;
                }
            }
            if (!ok1 && !ok2) return false;
        }
        return true;
    }
};