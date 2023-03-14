#include <bits/stdc++.h>

using namespace std;

// https://cp-algorithms.com/graph/min_cost_flow.html in O(E * V + E * logV * FLOW)
// negative-cost edges are allowed
// negative-cost cycles are not allowed

struct Edge {
    // 邻接点，对应的边编号，容量，流量，费用
    int to, rev, cap, f, cost;
};

// 本质上最小费用使用贪心的思想保证每一次寻找增广路都是寻找最小费用的路径
// 由于最大流是固定的，这就保证了贪心的正确性。
struct min_cost_flow {
    vector<vector<Edge>> graph;

    min_cost_flow(int nodes) : graph(nodes) {}

    void add_edge(int s, int t, int cap, int cost) {
        Edge a = {t, (int)graph[t].size(), cap, 0, cost};
        Edge b = {s, (int)graph[s].size(), 0, 0, -cost};
        graph[s].emplace_back(a);
        graph[t].emplace_back(b);
    }

    // Primal-Dual 原始对偶算法
    // 使用bellman_ford算法跑一次最短路计算得到势能
    // 允许出现负代价的路径，但是不能出现负代价的环
    void bellman_ford(int s, vector<int> &dist) {
        int n = graph.size();
        vector<int> q(n);
        vector<bool> inqueue(n);
        fill(dist.begin(), dist.end(), numeric_limits<int>::max());
        dist[s] = 0;
        // 这里是使用队列优化的BF，实际上就是SPFA
        int qt = 0;
        q[qt++] = s;
        for (int qh = 0; qh != qt; qh++) {
            // 队列的大小一般来说会大于节点总个数V
            int u = q[qh % n];
            inqueue[u] = false;
            for (auto &e : graph[u]) {
                // 选择具有可用容量的边
                if (e.cap <= e.f)
                    continue;
                int v = e.to;
                int ndist = dist[u] + e.cost;
                if (dist[v] > ndist) {
                    dist[v] = ndist;
                    if (!inqueue[v]) {
                        inqueue[v] = true;
                        q[qt++ % n] = v;
                    }
                }
            }
        }
    }

    // 使用狄克斯特拉算法计算最短路
    // 允许出现负代价的路径，但是不允许出现负代价的环
    void dijkstra(int s, vector<int> &pot, vector<int> &dist, vector<int> &curflow, vector<int> &prevnode,
                  vector<int> &prevedge) {
        // 使用小根堆来进行队列优化，使用的是边空间的遍历
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        q.emplace(0, s);
        fill(dist.begin(), dist.end(), numeric_limits<int>::max());
        dist[s] = 0;
        curflow[s] = numeric_limits<int>::max();
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            // 判重，去除无用项
            if (d != dist[u])
                continue;
            for (size_t i = 0; i < graph[u].size(); i++) {
                Edge &e = graph[u][i];
                int v = e.to;
                // 选择具有可用容量的边
                if (e.cap <= e.f)
                    continue;
                // 边权w的边重置为w+h[u]-h[v]
                // 三角形不等式可以证明这一点，即新的边权是非负的
                int nprio = dist[u] + e.cost + pot[u] - pot[v];
                if (dist[v] > nprio) {
                    dist[v] = nprio;
                    q.emplace(nprio, v);
                    // 记录前继的节点和边编号，然后回溯计算总费用
                    // 更新当前的流大小
                    prevnode[v] = u;
                    prevedge[v] = i;
                    curflow[v] = min(curflow[u], e.cap - e.f);
                }
            }
        }
    }

    // s为源点，t为汇点，maxf规定的最大流
    tuple<int, int> cal_min_cost_flow(int s, int t, int maxf) {
        size_t n = graph.size();
        vector<int> pot(n), curflow(n), dist(n), prevnode(n), prevedge(n);
        // 狄克斯特拉算法只能计算正边权的图
        // 所以如果图里面只有非负边权的图，那么bellman_ford就可以注释掉
        bellman_ford(s, pot);  
        int flow = 0;  // 最大流
        int flow_cost = 0;  // 最小费用
        while (flow < maxf) {
            dijkstra(s, pot, dist, curflow, prevnode, prevedge);
            // 没有增广路径
            if (dist[t] == numeric_limits<int>::max())
                break;
            // dist[i]为最短路径的费用和+pot[s]-pot[i],pot[s]=0
            for (size_t i = 0; i < n; i++)
                pot[i] += dist[i];
            // 获取当前增广的流，并且计算费用和更新残留网络
            int df = min(curflow[t], maxf - flow);
            flow += df;
            for (int v = t; v != s; v = prevnode[v]) {
                Edge &e = graph[prevnode[v]][prevedge[v]];
                e.f += df;
                graph[v][e.rev].f -= df;
                flow_cost += df * e.cost;
            }
        }
        return {flow, flow_cost};
    }
};

// Usage example
int main() {
    int capacity[][3] = {{0, 3, 2}, {0, 0, 2}, {0, 0, 0}};
    int nodes = 3;
    min_cost_flow mcf(nodes);
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            if (capacity[i][j] != 0)
                mcf.add_edge(i, j, capacity[i][j], 1);

    int s = 0;
    int t = 2;
    auto [flow, flow_cost] = mcf.cal_min_cost_flow(s, t, numeric_limits<int>::max());

    cout << (4 == flow) << endl;
    cout << (6 == flow_cost) << endl;
}
