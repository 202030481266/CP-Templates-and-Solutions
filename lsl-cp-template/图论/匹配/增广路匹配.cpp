#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Matching_(graph_theory)#In_unweighted_bipartite_graphs
// time complexity: O(E * V)
// 最简单的匹配方法：如果u1匹配了，那就寻找能不能给u1再找一个。
bool findPath(const vector<vector<int>> &graph, int u1, vector<int> &matching, vector<bool> &vis) {
    vis[u1] = true;
    for (int v : graph[u1]) {
        // u1只能从连接自己的边寻找到匹配
        int u2 = matching[v];
        if (u2 == -1 || (!vis[u2] && findPath(graph, u2, matching, vis))) {
            // v还没有匹配或者能够给v的匹配寻找到新的匹配
            matching[v] = u1;
            return true;
        }
    }
    return false;
}

tuple<int, vector<int>> max_matching(const vector<vector<int>> &graph, int n2) {
    int n1 = graph.size();
    vector<int> matching(n2, -1);
    int matches = 0;
    for (int u = 0; u < n1; u++) {
        vector<bool> vis(n1);
        // 每一次都从u出发寻找匹配，如果添加条件mathcing[u]!=-1得到的matching不是双向的
        // 但是得到的答案是正确的，并且可以加快常数速度
        if (findPath(graph, u, matching, vis))
            ++matches;
    }
    return {matches, matching};
}

// usage example
int main() {
    vector<vector<int>> g(5);
    g[0].push_back(3);
    g[0].push_back(4);
    g[1].push_back(3);
    g[1].push_back(4);
    g[2].push_back(3);
    g[2].push_back(4);
    g[3].push_back(0);
    g[3].push_back(1);
    g[3].push_back(2);
    g[4].push_back(0);
    g[4].push_back(1);
    g[4].push_back(2);

    auto [max_matching_cardinality, mapping] = max_matching(g, 5);

    cout << (4 == max_matching_cardinality) << endl;

    for (int x : mapping)
        cout << x << " ";
    cout << endl;
}
