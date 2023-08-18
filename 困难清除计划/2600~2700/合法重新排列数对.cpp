class Solution {
    typedef pair<int, int> pii;
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int n = pairs.size();
        unordered_map<int, int> in;
        unordered_map<int, int> out;
        unordered_map<int, vector<int>> g;
        unordered_set<int> num;
        for (auto& p : pairs) {
            ++in[p[1]];
            ++out[p[0]];
            num.emplace(p[1]);
            num.emplace(p[0]);
        }
        for (int i = 0; i < n; ++i) g[pairs[i][0]].emplace_back(pairs[i][1]);
        vector<int> a;
        vector<vector<int>> ans;
        vector<int> path;
        unordered_map<int, int> del;
        for (int v : num)
            if (out[v] != in[v]) a.push_back(v);
        int cur;
        if (a.empty()) {
            cur = pairs[0][0];
        }
        else {
            if (out[a[0]] > in[a[0]]) {
                cur = a[0];
            }
            else cur = a[1];
        }
        function<void(int)> dfs = [&](int u) {
            for (int i = del[u]; i < g[u].size(); i = del[u]) {
                del[u] = i + 1;
                dfs(g[u][i]);
            }
            path.push_back(u);
        };
        dfs(cur);
        for (int i = path.size() - 1; i >= 1; --i) {
            ans.emplace_back(vector<int>{path[i], path[i - 1]});
        }
        return ans;
    }
};