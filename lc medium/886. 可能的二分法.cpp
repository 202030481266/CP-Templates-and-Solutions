#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // 点覆盖，判断是否是一个二分图

        vector<int> g[n];
        vector<int> color(n,-1);

        for (auto e : dislikes) {
            g[e[0]-1].push_back(e[1]-1);
            g[e[1]-1].push_back(e[0]-1);
        }

        auto dfs = [&](int u, auto&& dfs_ref) -> bool {
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u]^1;
                    if (!dfs_ref(v, dfs_ref)) {
                        return false;
                    }
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
            return true;
        };
        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                color[i] = 0;
                if (!dfs(i, dfs)) {
                    return false;
                }
            }
        }
        return true;
    }
};