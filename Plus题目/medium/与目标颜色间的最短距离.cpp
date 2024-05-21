#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size(), last[n][3];
        vector left(n, vector<int>(3, -1));
        vector right(n, vector<int>(3, -1));
        auto cal = [&](vector<vector<int>>& last, int start, int end, int c) {
            // range(start, end, c)
            int pre[3] = {-1, -1, -1};
            for (int i = start; i != end; i += c) {
                pre[colors[i] - 1] = i;
                for (int j = 0; j < 3; ++j) {
                    last[i][j] = pre[j];
                }
            }
        };
        cal(left, 0, n, 1);
        cal(right, n - 1, -1, -1);
        vector<int> ans;
        for (auto& q : queries) {
            int i = q[0], c = q[1] - 1;
            if (left[i][c] == -1 && right[i][c] == -1) {
                ans.push_back(-1);
            }
            else {
                int res = INT_MAX;
                if (left[i][c] != -1) {
                    res = min(res, i - left[i][c]);
                }
                if (right[i][c] != -1) {
                    res = min(res, right[i][c] - i);
                }
                ans.push_back(res); 
            }
        }
        return ans;
    }
};
