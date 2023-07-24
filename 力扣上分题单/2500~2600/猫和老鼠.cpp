struct Node {
    int x, y, z;
    Node(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};
class Solution {
    int f[60][60][2], degree[60][60][2];  // use degree
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        queue<Node> q;
        for (int i = 1; i < n; ++i) {
            f[i][i][0] = f[i][i][1] = 2;
            q.emplace(Node(i, i, 0));
            q.emplace(Node(i, i, 1));
        }
        for (int i = 1; i < n; ++i) {
            f[0][i][0] = f[0][i][1] = 1;
            q.emplace(Node(0, i, 0));
            q.emplace(Node(0, i, 1));
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                degree[i][j][0] = graph[i].size();
                degree[i][j][1] = graph[j].size();
            }
        }
        for (int& v : graph[0]) {
            for (int i = 0; i < n; ++i) --degree[i][v][1];
        }
        while (!q.empty()) {
            Node cur = q.front();
            q.pop();
            if (cur.z == 0) {
                // mouse 
                for (int& v : graph[cur.y]) {
                    // v -> cur.y, cat move
                    if (v == 0) continue;
                    if (f[cur.x][v][1] == 0) {
                        if (f[cur.x][cur.y][0] == 2) {
                            f[cur.x][v][1] = 2;
                            q.emplace(Node(cur.x, v, 1));
                        }
                        else if (--degree[cur.x][v][1] == 0) {
                            // pre status is all done
                            f[cur.x][v][1] = 1;
                            q.emplace(Node(cur.x, v, 1));
                        }
                    }
                }
            }
            else {
                // cat
                for (int& v : graph[cur.x]) {
                    // v -> cur.x, mouse move
                    if (f[v][cur.y][0] == 0) {
                        if (f[cur.x][cur.y][1] == 1) {
                            f[v][cur.y][0] = 1;
                            q.emplace(Node(v, cur.y, 0));
                        }
                        else if (--degree[v][cur.y][0] == 0) {
                            f[v][cur.y][0] = 2;
                            q.emplace(v, cur.y, 0);
                        }
                    }
                }
            }
        }
        return f[1][2][0];
    }
};