// https://leetcode.cn/problems/find-weighted-median-node-in-tree/description/
using pii = pair<int,int>;
using ll = long long;

class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector g(n, vector<pii>());
        for (auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }
        vector f(n, vector<int>(18));
        vector dis(n, vector<ll>(18));
        vector<int> dep(n);
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            if (u != 0) {
                for (int i = 1; i < 18; i++) {
                    f[u][i] = f[f[u][i - 1]][i - 1];
                    dis[u][i] = dis[f[u][i - 1]][i - 1] + dis[u][i - 1];
                }
            }
            for (auto [v, w] : g[u]) {
                if (v != fa) {
                    dep[v] = dep[u] + 1;
                    f[v][0] = u;
                    dis[v][0] = w;
                    self(self, v, u);
                }
            }
        };
        dfs(dfs, 0, -1);
        auto lca = [&](int u, int v) -> array<ll, 3> {
            int rev = 0; 
            ll du = 0, dv = 0;
            if (dep[u] < dep[v]) {
                swap(u, v);
                rev = 1;
            }
            for (int i = 17; i >= 0; --i) {
                if (dep[f[u][i]] >= dep[v]) {
                    du += dis[u][i];
                    u = f[u][i];
                }
            }
            if (u == v) {
                if (rev) return {u, dv, du};
                return {u, du, dv};
            }
            for (int i = 17; i >= 0; --i) {
                if (f[u][i] != f[v][i]) {
                    du += dis[u][i];
                    dv += dis[v][i];
                    u = f[u][i];
                    v = f[v][i];
                }
            }
            du += dis[u][0];
            dv += dis[v][0];
            if (rev) swap(du, dv);
            return {f[u][0], du, dv};
        };
        vector<int> ans;
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            auto [l, du, dv] = lca(u, v);
            ll w = (du + dv + 1) / 2;
            if (u == l) {
                w = (du + dv) - w;
                dv = 0;
                for (int i = 17; i >= 0; --i) {
                    if (dep[f[v][i]] >= dep[l] && dv + dis[v][i] <= w) {
                        dv += dis[v][i];
                        v = f[v][i];
                    }
                }
                ans.push_back(v);
            }
            else if (v == l) {
                du = 0;
                for (int i = 17; i >= 0; --i) {
                    if (dep[f[u][i]] >= dep[l] && du + dis[u][i] < w) {
                        du += dis[u][i];
                        u = f[u][i];
                    }
                }
                ans.push_back(f[u][0]);
            }
            else {
                if (du == w) {
                    ans.push_back(l);
                }
                else if (du > w) {
                    du = 0;
                    for (int i = 17; i >= 0; --i) {
                        if (dep[f[u][i]] >= dep[l] && du + dis[u][i] < w) {
                            du += dis[u][i];
                            u = f[u][i];
                        }
                    }
                    ans.push_back(f[u][0]);
                }
                else {
                    w -= du;
                    w = dv - w; // 找到最上面的点满足 <= w
                    dv = 0;
                    for (int i = 17; i >= 0; --i) {
                        if (dep[f[v][i]] >= dep[l] && dv + dis[v][i] <= w) {
                            dv += dis[v][i];
                            v = f[v][i];
                        }
                    }
                    ans.push_back(v);
                }
            }
        }
        return ans;
    }
};