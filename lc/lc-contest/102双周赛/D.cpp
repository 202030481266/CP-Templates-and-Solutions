class Graph {
public:
    vector<vector<int>> dis;
    int n;
    Graph(int N, vector<vector<int>>& edges) {
        n = N;
        dis = vector(n, vector<int>(n, 0x3f3f3f3f));
        for (int i = 0; i < n; ++i) dis[i][i] = 0;
        for (auto &c : edges) dis[c[0]][c[1]] = c[2];
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    
    void addEdge(vector<int> edge) {
        if (dis[edge[0]][edge[1]] > edge[2]) {
            dis[edge[0]][edge[1]] = edge[2];
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][edge[0]] + dis[edge[1]][j] + edge[2]);
        }
    }
    
    int shortestPath(int node1, int node2) {
        return dis[node1][node2] == 0x3f3f3f3f ? -1 : dis[node1][node2];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */