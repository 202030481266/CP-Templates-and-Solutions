#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), cnt[m][m];
        memset(cnt, 0, sizeof(cnt));
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> tmp;
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1) {
                    tmp.push_back(j);
                }
            }
            for (int k = 0; k < tmp.size(); ++k) {
                for (int x = k + 1; x < tmp.size(); ++x) {
                    ans += cnt[tmp[k]][tmp[x]];
                    ++cnt[tmp[k]][tmp[x]];
                }
            }
        }
        return ans;
    }
};
