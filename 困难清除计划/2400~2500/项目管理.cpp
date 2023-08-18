class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        int non_group = m;
        for (auto& c : group) if (c == -1) c = non_group++;
        m = non_group;
        vector<int> V[m];
        set<pair<int, int>> group_edge_list;
        vector<int> g[n];
        vector<int> du(n);
        for (int i = 0; i < n; ++i) V[group[i]].emplace_back(i);
        for (int i = 0; i < n; ++i)
            for (int v : beforeItems[i]) {
                if (group[v] != group[i])
                    group_edge_list.emplace(group[v], group[i]);
                g[v].emplace_back(i);
                ++du[i];
            }
        vector<int> group_du(m, 0);
        vector<int> group_g[m];
        for (auto [u, v] : group_edge_list) {
            group_g[u].emplace_back(v);
            ++group_du[v];
        }
        queue<int> q;
        for (int i = 0; i < m; ++i) 
            if (group_du[i] == 0 && V[i].size() > 0) q.emplace(i);
        vector<int> topu;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topu.emplace_back(u);
            for (int v : group_g[u]) {
                --group_du[v];
                if (group_du[v] == 0)
                    q.emplace(v);
            }
        }
        int cnt = 0;
        for (int i = 0; i < m; ++i) if (V[i].size() > 0) ++cnt;
        if (topu.size() != cnt) return {};
        // group topu sort
        vector<int> ans;
        auto f = [&](int gp) -> vector<int> {
            queue<int> q;
            vector<int> res;
            for (int u : V[gp]) if (du[u] == 0) q.emplace(u);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                res.emplace_back(u);
                for (int v : g[u]) {
                    --du[v];
                    if (du[v] == 0 && group[v] == gp) q.emplace(v);
                }
            }
            if (res.size() < V[gp].size()) return {};
            return res;
        };
        for (int group : topu) {
            auto res = f(group);
            if (res.size() == 0) return {};
            for (int v : res)
                ans.emplace_back(v);
        }
        return ans;
    }
};