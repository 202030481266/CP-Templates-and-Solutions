// 如果真的需要用到threshold，就是NP困难问题
// 本质上只需要判断DFS是否可以连通即可，非常巧妙！
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int) {
        if (edges.size() < n - 1) {
            return -1;
        }

        vector<vector<pair<int, int>>> g(n);
        int max_w = 0;
        for (auto& e : edges) {
            int x = e[0], y = e[1], w = e[2];
            g[y].emplace_back(x, w);
            max_w = max(max_w, w);
        }

        vector<int> vis(n);
        auto check = [&](int upper) -> bool {
            int left = n;
            auto dfs = [&](this auto&& dfs, int x) -> void {
                vis[x] = upper; // 避免每次二分重新创建 vis 数组
                left--;
                for (auto& [y, w] : g[x]) {
                    if (w <= upper && vis[y] != upper) {
                        dfs(y);
                    }
                }
            };
            dfs(0);
            return left == 0;
        };

        int left = 0, right = max_w + 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right > max_w ? -1 : right;
    }
};