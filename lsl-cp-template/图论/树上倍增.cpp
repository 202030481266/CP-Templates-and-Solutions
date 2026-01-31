#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100005; // 根据题目要求调整最大节点数
const int LOGN = 17;     // log2(MAXN)的上界，保证2^LOGN >= MAXN

vector<int> adj[MAXN];   // 邻接表表示树
int up[MAXN][LOGN];      // up[v][k]表示节点v的第2^k个祖先
int depth[MAXN];         // 节点v的深度

void dfs(int v, int p) {
    up[v][0] = p;
    depth[v] = depth[p] + 1;
    for (int i = 1; i < LOGN; i++) {
        if (up[v][i - 1] != -1)
            up[v][i] = up[up[v][i - 1]][i - 1];
        else
            up[v][i] = -1;
    }
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    // 将u提升到和v同一深度
    for (int k = LOGN - 1; k >= 0; k--) {
        if (up[u][k] != -1 && depth[up[u][k]] >= depth[v])
            u = up[u][k];
    }
    if (u == v)
        return u;
    // 同时向上提升u和v
    for (int k = LOGN - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

int main() {
    memset(up, -1, sizeof(up));
    int n; // 节点数
    cin >> n;
    // 构建树
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v; // 输入节点编号，从1开始
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[0] = -1; // 假设根节点为1，它的父节点设为0
    dfs(1, 0);     // 从根节点开始DFS
    int q; // 查询次数
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int ancestor = lca(u, v);
        cout << ancestor << endl;
    }
    return 0;
}
