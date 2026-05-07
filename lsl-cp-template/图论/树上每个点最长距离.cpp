pair<vector<int>, int> bfs(int src, const vii& g, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    int farthest = src;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthest]) farthest = v;
            }
        }
    }
    return {dist, farthest};
}

void solve() {
    int n;
    cin >> n;
    vii g(n + 1);

    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto [_, A] = bfs(1, g, n);
    auto [distA, B] = bfs(A, g, n);
    auto [distB, __] = bfs(B, g, n);

    vi dis(n + 1);
    for (int u = 1; u <= n; ++u) {
        dis[u] = max(distA[u], distB[u]);
    }
}