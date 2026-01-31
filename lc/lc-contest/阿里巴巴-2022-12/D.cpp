class Solution {
public:
    int magnificentSets(int n, vector<vector<int>> &edges) {
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        int time[n], clock = 0; 
        memset(time, 0, sizeof(time));
        auto bfs = [&](int start) -> int {
            int depth = 0;
            time[start] = ++clock;
            vector<int> q = {start};
            while (!q.empty()) {
                vector<int> nxt;
                for (int x : q)
                    for (int y : g[x])
                        if (time[y] != clock) { 
                            time[y] = clock;
                            nxt.push_back(y);
                        }
                q = move(nxt);
                ++depth;
            }
            return depth;
        };

        int8_t color[n]; memset(color, 0, sizeof(color));
        vector<int> nodes;
        function<bool(int, int8_t)> is_bipartite = [&](int x, int8_t c) -> bool { 
            nodes.push_back(x);
            color[x] = c;
            for (int y : g[x])
                if (color[y] == c || color[y] == 0 && !is_bipartite(y, -c))
                    return false;
            return true;
        };

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (color[i]) continue;
            nodes.clear();
            if (!is_bipartite(i, 1)) return -1; 
            int max_depth = 0;
            for (int x : nodes) 
                max_depth = max(max_depth, bfs(x));
            ans += max_depth;
        }
        return ans;
    }
};

