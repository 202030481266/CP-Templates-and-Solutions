#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Hopcroft–Karp_algorithm
// time complexity: O(E * sqrt(V))
// 最常用的寻找二分图最大匹配的算法，基本思想在于寻找增广路径： 
// a-c-d-b，则匹配c-d可以转换为两个匹配a-c和d-b（未匹配的节点出发寻找奇数长度的简单路径）
// 同时也可以把这个算法看做Dinic算法的特例，使用最大流算法可以快速计算得到最大匹配

void bfs(const vector<vector<int>> &graph, vector<bool> &used, vector<int> &mapping, vector<int> &dist) {
    // 使用bfs求解最短路径
    fill(dist.begin(), dist.end(), -1);
    size_t n1 = graph.size();
    vector<int> Q(n1);
    int sizeQ = 0;
    for (int u = 0; u < n1; ++u) {
        // 每一次的增广路的起点都是没有匹配的距离为0的点
        if (!used[u]) {
            Q[sizeQ++] = u;
            dist[u] = 0;
        }
    }
    for (int i = 0; i < sizeQ; i++) {
        int u1 = Q[i];
        for (int v : graph[u1]) {
            int u2 = mapping[v];
            // 没有搜索过才进行dist更新
            if (u2 >= 0 && dist[u2] < 0) {
                dist[u2] = dist[u1] + 1;
                Q[sizeQ++] = u2;
            }
        }
    }
}

bool dfs(const vector<vector<int>> &graph, vector<bool> &vis, vector<bool> &used, vector<int> &matching,
         vector<int> &dist, int u1) {
    vis[u1] = true;
    for (int v : graph[u1]) {
        int u2 = matching[v];
        // 寻找增广路径并且保证只在bfs的下一层中寻找，这样就不会走回头路
        if (u2 < 0 || (!vis[u2] && dist[u2] == dist[u1] + 1 && dfs(graph, vis, used, matching, dist, u2))) {
            matching[v] = u1;
            used[u1] = true;
            return true;
        }
    }
    return false;
}

tuple<int, vector<int>> max_matching(const vector<vector<int>> &graph, int n2) {
    vector<int> mapping(n2, -1);  // 匹配的数组，它的大小和图的大小不一定相同
    size_t n1 = graph.size();
    vector<int> dist(n1);
    vector<bool> used(n1);
    for (int res = 0;;) {
        bfs(graph, used, mapping, dist);
        vector<bool> vis(n1);
        int f = 0;
        // 进行增广得到最大流
        for (int u = 0; u < n1; ++u)
            if (!used[u] && dfs(graph, vis, used, mapping, dist, u))
                ++f;
        if (f == 0)
            return {res, mapping};
        res += f;
    }
}

// usage example
int main() {
    vector<vector<int>> g(3);
    g[0].push_back(0);
    g[0].push_back(1);
    g[1].push_back(1);
    g[2].push_back(1);

    auto [max_matching_cardinality, mapping] = max_matching(g, 2);

    cout << (2 == max_matching_cardinality) << endl;

    for (int x : mapping)
        cout << x << " ";
    cout << endl;
}
