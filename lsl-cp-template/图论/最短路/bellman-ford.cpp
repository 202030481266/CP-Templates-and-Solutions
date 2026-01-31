/*
    Name: Bellman-Ford algorithm
    Time complexity: O(N * M)
    Space complexity: O(N + M)
*/
#include <bits/stdc++.h>

using namespace std;

// https://cp-algorithms.com/graph/bellman_ford.html
// 解决负边权的图最短路径问题

typedef pair<int, int> edge;

const int INF = numeric_limits<int>::max() / 3;

tuple<bool, vector<int>, vector<int>> bellman_ford(const vector<vector<edge>> &g, int s) {
    size_t n = g.size();
    vector<int> prio(n, INF);
    vector<int> pred(n, -1);
    prio[s] = 0;
    bool was_changed = true;
    for (int k = 0; k < n; k++) {
        was_changed = false;
        for (int u = 0; u < n; u++) {
            for (auto [v, cost] : g[u]) {
                if (prio[v] > prio[u] + cost) {
                    prio[v] = prio[u] + cost;
                    pred[v] = u;
                    was_changed = true;
                }
            }
        }
        if (!was_changed)
            break;
    }
    // 最多进行V-1次迭代和松弛如果超过这个次数表明就有负环产生
    // was_changed is true iff graph has a negative cycle
    return {was_changed, prio, pred};
}

vector<int> find_negative_cycle(const vector<vector<edge>> &g) {
    size_t n = g.size();
    vector<int> pred(n, -1);
    vector<int> prio(n, INF);
    prio[0] = 0;
    int last = 0;
    for (int k = 0; k < n; k++) {
        last = -1;
        for (int u = 0; u < n; u++) {
            for (auto [v, cost] : g[u]) {
                if (prio[v] > prio[u] + cost) {
                    prio[v] = prio[u] + cost;
                    pred[v] = u;
                    last = v;
                }
            }
        }
        // 判断方法和bellman_ford算法其实是一样的
        // 但是保留了最后一次迭代的负环上的节点
        if (last == -1)
            return {};
    }
    vector<int> path(n);
    vector<int> pos(n, -1);
    for (int i = 0;; i++) {
        // 寻找负环上的前继，直到回到一开始的last开始的位置
        if (pos[last] != -1)
            return vector<int>(path.rend() - i, path.rend() - pos[last]);
        path[i] = last;
        pos[last] = i;
        last = pred[last];
    }
}

int main() {
    vector<vector<edge>> g(4);
    g[0].emplace_back(1, 1);
    g[1].emplace_back(0, 1);
    g[1].emplace_back(2, 1);
    g[2].emplace_back(3, -10);
    g[3].emplace_back(1, 1);

    vector<int> cycle = find_negative_cycle(g);
    for (int u : cycle)
        cout << u << " ";
}
