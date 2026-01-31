#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vii = vector<vi>;


class Solution {
public:
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center, int radius) {
        using pii = pair<int, int>;
        pii ans{-1, -1};
        int mx = -1;
        for (auto& p : towers) {
            int x = p[0], y = p[1], w = p[2];
            int dis = abs(x - center[0]) + abs(y - center[1]);
            if (dis <= radius) {
                if (w > mx || w == mx && make_pair(x, y) < ans) ans = {x, y}, mx = w; 
            }
        }
        return {ans.first, ans.second};
    }
};
