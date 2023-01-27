#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Topological_sorting

void dfs(const vector<vector<int>> &graph, vector<bool> &used, vector<int> &order, int u) {
    // 一直往前搜索直到终点
    used[u] = true;
    for (int v : graph[u])
        if (!used[v])
            dfs(graph, used, order, v);
    order.push_back(u);
}

vector<int> topological_sort(const vector<vector<int>> &graph) {
    size_t n = graph.size();
    vector<bool> used(n);
    vector<int> order;
    // 拓扑图由许多节点的拓扑结构组成，所以可以使用dfs来遍历每一个拓扑结构
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(graph, used, order, i);
    // 因为是倒序的，要翻转过来
    reverse(order.begin(), order.end());
    return order;
}

// usage example
int main() {
    vector<vector<int>> g = {{0}, {}, {0, 1}};

    vector<int> order = topological_sort(g);

    for (int v : order)
        cout << v << " ";
    cout << endl;
}
