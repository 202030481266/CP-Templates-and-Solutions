#include <vector>
#include <array>
#include <algorithm>

struct TreeDistance {
    int n;
    std::vector<int> depth;
    std::vector<std::array<int, 21>> up;

    TreeDistance(const std::vector<std::vector<int>>& g) {
        n = (int)g.size() - 1;
        if (n <= 0) return;
        depth.assign(n + 1, 0);
        up.assign(n + 1, std::array<int, 21>{});

        std::vector<int> q(n);
        int head = 0, tail = 0;
        
        q[tail++] = 1;
        depth[1] = 1;
        
        while (head < tail) {
            int u = q[head++];
            for (int v : g[u]) {
                if (v != up[u][0]) {
                    depth[v] = depth[u] + 1;
                    up[v][0] = u;
                    q[tail++] = v;
                }
            }
        }
        
        for (int j = 1; j <= 20; j++) {
            for (int i = 1; i <= n; i++) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }

    int get_lca(int u, int v) const {
        if (depth[u] < depth[v]) std::swap(u, v);
        for (int j = 20; j >= 0; j--) {
            if (depth[u] - (1 << j) >= depth[v]) {
                u = up[u][j];
            }
        }
        if (u == v) return u;
        for (int j = 20; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int get_dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
};