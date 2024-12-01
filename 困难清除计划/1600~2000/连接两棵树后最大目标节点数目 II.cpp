#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size()+1, m = edges2.size()+1; 
        vector g1(n, vector<int>());
        vector g2(m, vector<int>());

        for (auto& e : edges1) {
            int u = e[0], v = e[1];
            g1[u].push_back(v);
            g1[v].push_back(u);
        }
        for (auto& e : edges2) {
            int u = e[0], v = e[1];
            g2[u].push_back(v);
            g2[v].push_back(u);
        }

        vector c1(n, vector<int>(2));
        vector c2(m, vector<int>(2));
        vector<int> dep(n);

        auto dfs = [&](int u, int fa, vector<vector<int>>& g, vector<vector<int>>& c, auto&& dfs_ref) -> void {
            c[u][0] = 1;
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs_ref(v, u, g, c, dfs_ref);
                    c[u][0] += c[v][1];
                    c[u][1] += c[v][0];
                }
            }
        };
        dfs(0, 0, g1, c1, dfs);
        dfs(0, 0, g2, c2, dfs);

        auto cal = [&](int u, int fa, vector<vector<int>>& g, auto&& dfs_ref) -> void {
            dep[u] = dep[fa] ^ 1;
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs_ref(v, u, g, dfs_ref);
                }
            }
        };
        cal(0, 0, g1, cal);

        int mx = 0;
        if (c1[0][0]) mx = max(mx, c2[0][1]);
        if (c1[0][1]) mx = max(mx, c2[0][0]);
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = mx + c1[0][dep[i] ^ dep[0]];
        }
        return ans;
    }
};