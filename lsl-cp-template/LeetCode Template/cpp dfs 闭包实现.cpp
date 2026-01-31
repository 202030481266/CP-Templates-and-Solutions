#include <iostream>
#include <vector>

void dfsExample(const std::vector<std::vector<int>>& graph, int start) {
    // 使用 lambda 表达式实现递归 DFS
    auto dfs = [&](int node, auto& dfs_ref) -> void {
        std::cout << "Visiting node: " << node << std::endl;

        for (int neighbor : graph[node]) {
            // 在递归调用中传入 lambda 自身
            dfs_ref(neighbor, dfs_ref);
        }
    };

    // 初始调用传递 lambda 本身
    dfs(start, dfs);
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},    // 节点 0 的邻接表
        {3},       // 节点 1 的邻接表
        {3},       // 节点 2 的邻接表
        {}         // 节点 3 的邻接表
    };

    dfsExample(graph, 0);
    return 0;
}

