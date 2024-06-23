#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        // 动态维护最近点对
        // 除了暴力没有好的方法
        map<int, vector<pii>> mp;
        int n = workers.size(), m = bikes.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int dis = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1]);
                mp[dis].push_back({i, j});
            }
        }
        vector<bool> vis(m, false);
        vector<int> ans(n, -1);
        for (auto [k, v] : mp) {
            sort(v.begin(), v.end());
            for (auto [i, j] : v) {
                if (vis[j] || ans[i] > -1) continue;
                ans[i] = j;
                vis[j] = true;
            }
        }
        return ans;
    }
};