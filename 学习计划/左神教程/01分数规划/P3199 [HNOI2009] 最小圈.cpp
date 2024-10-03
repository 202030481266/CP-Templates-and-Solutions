#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int maxn = 10010;
const double eps = 1e-8;
const int inf = 1e12;
int n, m;
// use edge base graph
struct Edge {
    int u, v;
    double weight;
};

#include <vector>
#include <stack>


int find_src(int n, int m, std::vector<Edge>& G) {
    // 构建邻接表
    std::vector<std::vector<int>> adj(n);
    for(auto &edge : G){
        adj[edge.u].push_back(edge.v);
    }

    // 第一步：找到候选母顶点
    std::vector<bool> visited(n, false);
    int candidate = -1;

    for(int i = 0; i < n; ++i){
        if(!visited[i]){
            // 使用栈实现迭代版DFS
            std::stack<int> s;
            s.push(i);
            while(!s.empty()){
                int u = s.top();
                s.pop();
                if(!visited[u]){
                    visited[u] = true;
                    for(auto &v : adj[u]){
                        if(!visited[v]){
                            s.push(v);
                        }
                    }
                    candidate = u; // 记录最后访问的节点
                }
            }
        }
    }

    // 第二步：验证候选母顶点是否真的可以到达所有节点
    std::fill(visited.begin(), visited.end(), false);
    std::stack<int> s;
    s.push(candidate);
    while(!s.empty()){
        int u = s.top();
        s.pop();
        if(!visited[u]){
            visited[u] = true;
            for(auto &v : adj[u]){
                if(!visited[v]){
                    s.push(v);
                }
            }
        }
    }

    // 根据题目保证，必存在一个可以到达所有节点的源点
    // 因此不需要额外的验证，直接返回候选母顶点
    return candidate;
}

// Bellman-Ford算法，返回图中是否存在负权环
bool bellman_ford(int V, int E, vector<Edge>& edges, int src, double val) {
    // Step 1: 初始化距离数组，源点到自身距离为0，其他点为无限大
    vector<double> dist(V, inf);
    dist[src] = 0;

    // Step 2: 执行 V-1 次松弛操作
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].u;
            int v = edges[j].v;
            double weight = edges[j].weight - val;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: 检查是否有负环，进行第 V 次松弛操作
    for (int j = 0; j < E; ++j) {
        int u = edges[j].u;
        int v = edges[j].v;
        double weight = edges[j].weight - val;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            // 如果在第 V 次松弛时还能更新，说明存在负环
            // cout << "图中存在负权环" << endl;
            return true;
        }
    }

    // cout << "图中不存在负权环" << endl;
    return false;
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    vector<Edge> g(m);
    for (int i = 0; i < m; ++i) {
        cin >> g[i].u >> g[i].v >> g[i].weight;
        --g[i].u;
        --g[i].v;
    }

    double l = -10000, r = 10000;
    int src = find_src(n, m, g);
    
   for (int iter = 0; iter < 50; iter++) {
        double mid = (l+r) / 2;
        if (bellman_ford(n, m, g, src, mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    
    cout << fixed << setprecision(8) << l << endl;

    return 0;
}