#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 5005; // 最大节点数
const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

vector<Edge> adj[MAXN]; // 邻接表
int dist[MAXN];         // 距离数组
int cnt[MAXN];          // 记录节点入队次数
bool inQueue[MAXN];     // 标记节点是否在队列中

bool SPFA(int n, int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    memset(inQueue, false, sizeof(inQueue));

    queue<int> q;
    dist[s] = 0;
    q.push(s);
    inQueue[s] = true;
    cnt[s] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (const Edge& e : adj[u]) {
            int v = e.to;
            if (dist[v] > dist[u] + e.weight) {
                dist[v] = dist[u] + e.weight;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n) {
                        // 检测到负环
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; // n 为变量数量，m 为不等式数量
    cin >> n >> m;
    // 构建图
    for (int i = 0; i < m; ++i) {
        int type, xi, xj, c;
        cin >> type >> xi >> xj;
        if (type != 3) cin >> c;
        // X_i - X_j ≤ c  转化为 从 xj 到 xi 的边，权值为 c
        if (type == 1) {
            adj[xi].push_back({xj, -c});
        }
        else if (type == 2) {
            adj[xj].push_back({xi, c});
        }
        else {
            // xi == xj, xi <= xj + 0, xj <= xi + 0
            adj[xi].push_back({xj, 0});
            adj[xj].push_back({xi, 0});
        }
    }

    // 添加超级源点 0
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        adj[s].push_back({i, 0});
    }

    if (SPFA(n + 1, s)) {
        // 无负环，输出解
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}