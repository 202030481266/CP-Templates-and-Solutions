class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        if (m != n - 1) return false;
        vector<int> cnt(n);
        vector<int> g[n];
        for (auto& e : edges) {
            ++cnt[e[0]];
            ++cnt[e[1]];
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (cnt[i] == 1) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                --cnt[v];
                if (cnt[v] == 1) {
                    q.push(v);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (cnt[i] > 1) return false;
        }
        return true;
    }
};