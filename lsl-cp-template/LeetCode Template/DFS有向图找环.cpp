#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Graph {
    int V; // 顶点数
    vector<vector<int>> adj; // 邻接表

public:
    Graph(int V) : V(V), adj(V) {}

    // 添加边
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // 找到所有环
    void findCycles(vector<vector<int>>& cycles) {
        for (int start = 0; start < V; ++start) {
            vector<int> path;
            bitset<26> visited; // 使用位掩码记录访问状态
            dfsFindCycles(start, start, path, visited, cycles);
        }
    }

private:
    // 辅助函数：DFS 查找环
    void dfsFindCycles(int start, int u, vector<int>& path, bitset<26>& visited, vector<vector<int>>& cycles) {
        path.push_back(u);
        visited.set(u);

        for (int v : adj[u]) {
            if (v == start && path.size() > 1) { // 找到环
                cycles.push_back(path);
            } else if (!visited.test(v)) { // 如果节点未被访问
                dfsFindCycles(start, v, path, visited, cycles);
            }
        }

        path.pop_back();
        visited.reset(u);
    }
};

int main() { // 小规模图更加有优势
    int V = 5;
    Graph g(V);

    // 添加边
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 2);

    // 找到所有环
    vector<vector<int>> cycles;
    g.findCycles(cycles);

    // 输出环
    cout << "Found cycles:\n";
    for (auto& cycle : cycles) {
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}