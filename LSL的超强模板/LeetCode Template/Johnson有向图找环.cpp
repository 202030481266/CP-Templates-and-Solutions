#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Graph {
    int V; // 顶点数
    map<int, vector<int>> adj; // 邻接表

public:
    Graph(int V) : V(V) {}

    // 添加边
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // 找到所有强连通分量（SCC）
    void findSCCs(vector<vector<int>>& sccs) {
        vector<int> disc(V, -1), low(V, -1);
        vector<bool> inStack(V, false);
        stack<int> st;
        int time = 0;

        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                findSCCUtil(i, disc, low, st, inStack, sccs, time);
            }
        }
    }

    // 使用 Johnson 算法找到所有环
    void findCycles(vector<vector<int>>& cycles) {
        vector<vector<int>> sccs;
        findSCCs(sccs); // 找到所有强连通分量

        for (auto& scc : sccs) {
            if (scc.size() > 1) { // 只处理大小大于1的强连通分量
                for (int start : scc) {
                    vector<int> path;
                    set<int> blocked;
                    map<int, set<int>> blockedMap;
                    dfsFindCycles(start, start, path, blocked, blockedMap, cycles);
                }
            }
        }
    }

private:
    // 辅助函数：找到强连通分量
    void findSCCUtil(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& inStack, vector<vector<int>>& sccs, int& time) {
        disc[u] = low[u] = ++time;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                findSCCUtil(v, disc, low, st, inStack, sccs, time);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            vector<int> scc;
            while (st.top() != u) {
                int v = st.top();
                st.pop();
                inStack[v] = false;
                scc.push_back(v);
            }
            st.pop();
            inStack[u] = false;
            scc.push_back(u);
            sccs.push_back(scc);
        }
    }

    // 辅助函数：DFS 查找环
    bool dfsFindCycles(int start, int u, vector<int>& path, set<int>& blocked, map<int, set<int>>& blockedMap, vector<vector<int>>& cycles) {
        bool foundCycle = false;
        path.push_back(u);
        blocked.insert(u);

        for (int v : adj[u]) {
            if (v == start) { // 找到环
                cycles.push_back(path);
                foundCycle = true;
            } else if (blocked.find(v) == blocked.end()) { // 如果节点未被阻塞
                if (dfsFindCycles(start, v, path, blocked, blockedMap, cycles)) {
                    foundCycle = true;
                }
            }
        }

        if (foundCycle) {
            unblock(u, blocked, blockedMap);
        } else {
            for (int v : adj[u]) {
                blockedMap[v].insert(u);
            }
        }

        path.pop_back();
        return foundCycle;
    }

    // 辅助函数：解除节点的阻塞
    void unblock(int u, set<int>& blocked, map<int, set<int>>& blockedMap) {
        blocked.erase(u);
        for (int v : blockedMap[u]) {
            if (blocked.find(v) != blocked.end()) {
                unblock(v, blocked, blockedMap);
            }
        }
        blockedMap[u].clear();
    }
};

int main() { // 不能找到自环
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