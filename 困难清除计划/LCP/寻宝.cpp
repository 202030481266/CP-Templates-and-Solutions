class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int N, n, m;
public:
    void bfs(int start, vector<int>& dis, vector<string>& maze) {
        dis[start] = 0;
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int x = (u / m) + dirs[i][0], y = (u % m) + dirs[i][1], v = x * m + y;
                if (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != '#' && dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    int minimalSteps(vector<string>& maze) {
        // N = 10000

        n = maze.size(), m = maze[0].size(), N = n * m;

        // the path should be S -> O -> M1 -> O -> M2 -> O -> M3 -> .... O -> Mi -> ... -> Mk -> T,
        // 就是对于所有的M，到达的状态最多有 2^16
        int M, S, T;
        vector<int> mech, rock;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == 'M') mech.push_back(i * m + j);
                else if (maze[i][j] == 'O') rock.push_back(i * m + j);
                else if (maze[i][j] == 'S') S = i * m + j;
                else if (maze[i][j] == 'T') T = i * m + j; 
            }

        M = mech.size();
        vector<vector<int>> dp(M, vector<int>(1 << M, 0x3f3f3f3f));

        // 计算需要的最短路
        vector<int> dis_from_T(N, 0x3f3f3f3f), dis_from_S(N, 0x3f3f3f3f);
        vector<vector<int>> dis_from_M(M, vector<int>(N, 0x3f3f3f3f));
        vector<vector<int>> dis(M, vector<int>(M, 0x3f3f3f3f));
        bfs(S, dis_from_S, maze); 
        bfs(T, dis_from_T, maze);
        for (int i = 0; i < M; ++i) bfs(mech[i], dis_from_M[i], maze);

        if (M == 0) return dis_from_S[T] == 0x3f3f3f3f ? -1 : dis_from_S[T];
        // dis[i][j] 表示第i个机关到第j个机关的最短 M-O-M 路径长度
        for (int i = 0; i < M; ++i)
            for (int j = i + 1; j < M; ++j) {
                int tmp = 0x3f3f3f3f;
                for (int k = 0; k < rock.size(); ++k) 
                    tmp = min(tmp, dis_from_M[i][rock[k]] + dis_from_M[j][rock[k]]);
                dis[i][j] = dis[j][i] = tmp;
            }

        // 
        for (int i = 0; i < M; ++i) {
            int& r = dp[i][(1 << i)];
            for (int k = 0; k < rock.size(); ++k)
                r = min(r, dis_from_S[rock[k]] + dis_from_M[i][rock[k]]);
        }
        // 动态规划
        for (int status = 3; status < (1 << M); ++status) {
            for (int i = 0; i < M; ++i) {
                // 计算 dp[i][status]
                int& d = dp[i][status];
                if (!((status >> i) & 1)) continue;
                if (d != 0x3f3f3f3f) continue; // 已经计算过了
                for (int j = 0; j < M; ++j) {
                    if ((status >> j) & 1) {
                        d = min(d, dp[j][status ^ (1 << i)] + dis[i][j]);
                    }
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < M; ++i) {
            ans = min(ans, dp[i][(1 << M) - 1] + dis_from_T[mech[i]]);
        }
        return (ans == 0x3f3f3f3f ? -1 : ans);
    }
};