#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int maximumSubtreeSize(vector<vector<int>>& edges, vector<int>& colors) {
        int n = colors.size();
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int ans = 1;
        function<int(int, int)> dfs = [&](int u, int fa) {
            int res = 1;
            bool same = true;
            for (int v : g[u]) {
                if (v == fa) continue;
                int tmp = dfs(v, u);
                same &= tmp > 0;
                res += tmp;
            }
            if (same) ans = max(ans, res); // 这棵树的颜色都是colors[u]
            return colors[u] == colors[fa] && same ? res : 0;
        };
        dfs(0, 0);
        return ans;
    }
};