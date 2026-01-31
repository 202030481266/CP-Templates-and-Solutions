#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<pair<int, int>> a;
        for (auto& interval : intervals) {
            a.push_back({interval[0], 1});
            a.push_back({interval[1], -1});
        }
        a.push_back({toBeRemoved[0], -1});
        a.push_back({toBeRemoved[1], 1});
        sort(a.begin(), a.end());
        vector<vector<int>> ans;
        int cur = 0, l = inf;
        for (auto [x, y] : a) {
            cur += y;
            if (cur == 0 && l != inf) {
                ans.push_back({l, x});
                l = inf;
            }
            else if (cur > 0) {
                l = x;
            }
        }
        return ans;
    }
};
