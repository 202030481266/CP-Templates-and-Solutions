#include <vector>

std::vector<int> getDiameter(const std::vector<std::vector<int>>& g) { // 1-index undirected tree
    int n = (int)g.size() - 1;
    if (n <= 0) return {};
    
    std::vector<int> q(n);
    std::vector<int> pre(n + 1);
    
    auto get_farthest = [&](int start) {
        int head = 0, tail = 0;
        q[tail++] = start;
        pre[start] = -1;
        int farthest = start;
        
        while (head < tail) {
            int u = q[head++];
            farthest = u;
            for (int v : g[u]) {
                if (v != pre[u]) {
                    pre[v] = u;
                    q[tail++] = v;
                }
            }
        }
        return farthest;
    };

    int S = get_farthest(1);
    int T = get_farthest(S);

    std::vector<int> path;
    for (int u = T; u != -1; u = pre[u]) {
        path.push_back(u);
    }
    
    return path;
}