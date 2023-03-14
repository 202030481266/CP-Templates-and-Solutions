#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Dinic%27s_algorithm in O(V^2 * E)
// 在具有单位流量（边容量都是1）的网络中复杂度更低

struct Edge {
    // 表示边邻接点，对称的边编号，容量，流量
    int to, rev, cap, f;
};
struct max_flow_dinic {
    vector<vector<Edge>> graph;  // 图
    vector<int> dist;  // 残留网络的距离计算数组

    // 节点个数初始化，nodes=V
    max_flow_dinic(int nodes) : graph(nodes), dist(nodes) {}

    void add_edge(int s, int t, int cap) {
        // 构建初始的网络G
        Edge a = {t, (int)graph[t].size(), cap, 0};
        Edge b = {s, (int)graph[s].size(), cap, 0};
        graph[s].emplace_back(a);
        graph[t].emplace_back(b);
    }

    // 计算残留网络的标记距离，使用bfs算法可以在O(E)复杂度计算
    // src为源点，dest是汇点
    bool dinic_bfs(int src, int dest) {
        fill(dist.begin(), dist.end(), -1);
        dist[src] = 0;
        // 手写队列，使用STL的vector实现
        vector<int> q(graph.size());
        int qt = 0;
        q[qt++] = src;
        for (int qh = 0; qh < qt; qh++) {
            int u = q[qh];
            for (auto &e : graph[u]) {
                int v = e.to;
                // 选择具有可用容量的边进行搜索
                if (dist[v] < 0 && e.f < e.cap) {
                    dist[v] = dist[u] + 1;
                    q[qt++] = v;
                }
            }
        }
        return dist[dest] >= 0;
    }

    // 计算完残留网络的距离标记后进行阻塞流的构建
    int dinic_dfs(vector<int> &ptr, int u, int dest, int f) {
        if (u == dest)
            return f;
        // 这里使用了当前弧优化，可以有效防止一个节点走同样的重复的无效的边
        for (int &i = ptr[u]; i < (int)graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (e.cap <= e.f)
                continue;
            int v = e.to;
            // Dinic算法的核心特点在于选择最短的边进行增广
            // 这样就可以保证最多有n-1条增广路径
            if (dist[v] == dist[u] + 1) {
                int df = dinic_dfs(ptr, v, dest, min(f, e.cap - e.f));
                if (df > 0) {
                    e.f += df;
                    graph[v][e.rev].f -= df;
                    return df;
                }
            }
        }
        return 0;
    }

    int max_flow(int src, int dest) {
        int flow = 0;
        // 一直增广，直到算法无法在残留网络中找到增广路径，得到最大流
        while (dinic_bfs(src, dest)) {
            vector<int> ptr(graph.size());
            while (int delta = dinic_dfs(ptr, src, dest, numeric_limits<int>::max()))
                flow += delta;
        }
        return flow;
    }

    // invoke after max_flow()
    // 计算最小割里面的节点，最小割等于最大流定理可以得到最后的网络距离标记中非负的就是最小割
    vector<bool> min_cut() {
        vector<bool> cut(graph.size());
        for (size_t i = 0; i < cut.size(); ++i) {
            cut[i] = dist[i] != -1;
        }
        return cut;
    }

    // 清除之后可以方便计算各种源点和汇点的最大流
    void clear_flow() {
        for (auto &v : graph)
            for (Edge &e : v)
                e.f = 0;
    }
};
