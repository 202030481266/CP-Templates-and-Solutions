/*
    Name: Hierholzer's algorithm

    Time complexity: O(M)
    Space complexity: O(N + M)
*/

const int N = 1e5 + 10;

struct Edge {
    int adj;
    list<Edge>::iterator inv;
    Edge() {}
    Edge(int _adj) : adj(_adj) {}
};
struct Hierholzer {
    vector<list<Edge>> g;
    vector<int> path;

    Hierholzer() {}
    Hierholzer(int N): g(N + 1) {}  // 0~N-1或者1~N

    // 添加无向边 u-v
    void add_edge(int u, int v) {
        g[u].emplace_front(v);
        g[v].emplace_front(u);
        g[u].begin()->inv = g[v].begin();
        g[v].begin()->inv = g[u].begin();
    }
    // dfs搜索寻找欧拉路径
    void dfs(int v) {
        while (g[v].size() > 0) {
            int adj = g[v].front().adj;
            // 删除两条边
            g[adj].erase(g[v].front().inv);
            g[v].pop_front();
            dfs(adj);
        }
        path.emplace_back(v);
    }
};




