#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


// 一开始想错了以为是和深度有关系的（心算模型出错）
// 这说明人类在饥饿状态下很容易发挥失常

class Solution {
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1, f[n], d[n];
        memset(f, 0, sizeof(f));
        memset(d, 0, sizeof(d));

        vector<int> g[n];
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        function<void(int,int)> dfs = [&](int u, int fa) {
            for (int& v : g[u]) {
                if (v == fa)continue;
                dfs(v,u);
                int cost=(v&1 ? 1 : 2);
                if (f[v]+cost > f[u]) {
                    d[u]=f[u];
                    f[u] = f[v]+cost;
                }
                else if(f[v]+cost > d[u]) d[u]=f[v]+cost;
            }
        };
        dfs(0,-1);
        vector<int> dp(n);
        function<void(int,int,int)> dfs2 = [&](int u, int fa, int up) {
            dp[u] = max(f[u], up);
            for (int& v : g[u]) {
                if (v == fa) continue;
                int new_up = up, t = (v & 1 ? 1 : 2);
                if (f[u] == t + f[v]) new_up = max(new_up, d[u]);
                else new_up = max(new_up, f[u]);
                new_up += (u & 1 ? 1 : 2);
                dfs2(v, u, new_up);
            }
        };
        dfs2(0, 0, 0);
        return dp;
    }
};