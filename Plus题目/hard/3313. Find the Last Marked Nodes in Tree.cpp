#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 树上dp

class Solution {
public:
    vector<int> lastMarkedNodes(vector<vector<int>>& edges) {
        int n = edges.size()+1;
        vector<int> g[n];
        for (auto e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // depth of a node, and the node it can reach most depth, second depth
        vector<int> dep(n), mx(n), sc(n, -1);

        function<void(int,int)> dfs1 = [&](int u, int fa) {
            dep[u] = dep[fa] + 1;
            mx[u] = u;
            for (int v : g[u]) {
                if (v != fa) {
                    dfs1(v, u);
                    if (dep[mx[v]] > dep[mx[u]]) {
                        sc[u] = mx[u];
                        mx[u] = mx[v];
                    }
                    else if (sc[u] == -1 || dep[mx[v]] > dep[sc[u]]) {
                        sc[u] = mx[v];
                    }
                }
            }
        };
        dfs1(0, 0);

        vector<int> ans(n);
        ans[0] = mx[0];

        function<void(int,int,int,int)> dfs = [&](int u, int fa, int x, int y) {
            for (int v : g[u]) {
                if (v != fa) {
                    int dv = dep[mx[v]] - dep[v], k = (mx[v] == mx[u] ? sc[u] : mx[u]);
                    int du = dep[k] - dep[u] + 1;
                    // fa -> u -> v -> ... mx[v]
                    int mx_val = max(dv, max(du, x+1));
                    if (mx_val == dv) ans[v] = mx[v];
                    else if (mx_val == du) ans[v] = k;
                    else ans[v] = y;
                    if (du > x+1) {
                        dfs(v, u, du, k);
                    }
                    else {
                        dfs(v, u, x+1, y);
                    }
                }
            }
        };
        dfs(0,-1,-1,-1);

        return ans;
    }
};

// 树的直径的做法：对于任意节点 i，距离它最远的节点一定是树的直径的某个端点（反证法证明）

class Solution {
public:
    vector<int> lastMarkedNodes(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // 定义一个 BFS 函数，返回最远的节点和所有节点到起点的距离
        auto bfs = [&](int start) {
            vector<int> dist(n, -1);
            queue<int> q;
            q.push(start);
            dist[start] = 0;
            int farthestNode = start;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : g[u]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                        if (dist[v] > dist[farthestNode]) {
                            farthestNode = v;
                        }
                    }
                }
            }
            return make_pair(farthestNode, dist);
        };

        // 第一次 BFS，找到直径的一个端点
        auto p1 = bfs(0);
        int u = p1.first;

        // 第二次 BFS，找到直径的另一个端点
        auto p2 = bfs(u);
        int v = p2.first;

        // 获取所有节点到直径两个端点的距离
        auto dist_u = p2.second;
        auto dist_v = bfs(v).second;

        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            if (dist_u[i] >= dist_v[i]) {
                ans[i] = u;
            } else {
                ans[i] = v;
            }
        }
        return ans;
    }
};


