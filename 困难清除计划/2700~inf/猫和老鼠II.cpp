typedef tuple<int, int, int> tiii;
class Solution {
    int dp[64][64][2], d[64][64][2];
public:
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        int n = grid.size(), m = grid[0].size(), N = n * m;
        int food, cat, mouse;
        vector<int> g(N, 1);
        vector valid(n, vector<int>(m, 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'C') cat = i * m + j;
                else if (grid[i][j] == 'M') mouse = i * m + j;
                else if (grid[i][j] == 'F') food = i * m + j;
                else if (grid[i][j] == '#') valid[i][j] = g[i * m + j] = 0;
            }
        }
        // up down left right
        vector dir(N, vector<int>(4));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int id = i * m + j;
                if (g[id]) {  
                    while (i - dir[id][0] >= 0 && valid[i - dir[id][0]][j]) ++dir[id][0];
                    while (i + dir[id][1] < n && valid[i + dir[id][1]][j]) ++dir[id][1];
                    while (j - dir[id][2] >= 0 && valid[i][j - dir[id][2]]) ++dir[id][2];
                    while (j + dir[id][3] < m && valid[i][j + dir[id][3]]) ++dir[id][3];
                }
            }
        }
        auto f = [&](int type, int offset, int x, int y) -> int {
            if (type == 0) return (x - offset) * m + y;  // up
            else if (type == 1) return (x + offset) * m + y; // down
            else if (type == 2) return x * m + (y - offset); // left
            else return x * m + (y + offset); // right;
        };
        queue<tiii> q;
        for (int i = 0; i < N; ++i) {
            if (i != food && g[i]) {
                dp[food][i][1] = dp[food][i][0] = 1;  // mouse win
                dp[i][food][1] = dp[i][food][0] = 2;  // cat win
                dp[i][i][1] = dp[i][i][0] = 2; // cat win
                q.emplace(food, i, 1); q.emplace(food, i, 0);
                q.emplace(i, food, 1); q.emplace(i, food, 0);
                q.emplace(i, i, 1); q.emplace(i, i, 0);
            }
        }
        // caculat the degree of status
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != food && j != food && i != j && g[i] && g[j]) {
                    for (int k = 0; k < 4; ++k) d[i][j][0] += min(mouseJump, dir[i][k] - 1);
                    for (int k = 0; k < 4; ++k) d[i][j][1] += min(catJump, dir[j][k] - 1);
                    ++d[i][j][0];
                    ++d[i][j][1];
                }
            }
        }
        while (!q.empty()) {
            auto [i, j, turn] = q.front();
            q.pop();
            if (turn == 0) {
                // mouse move, so the pre move is cat
                int catx = j / m, caty = j % m, id;
                for (int k = 0; k < 4; ++k) {
                    for (int x = 1; x <= min(catJump, dir[j][k] - 1); ++x) {
                        id = f(k, x, catx, caty);
                        if (dp[i][id][1] == 0) {
                            if (dp[i][j][0] == 2) {
                                dp[i][id][1] = 2;
                                q.emplace(i, id, 1);
                            }
                            else {
                                --d[i][id][1];
                                if (d[i][id][1] == 0) {
                                    dp[i][id][1] = 1;
                                    q.emplace(i, id, 1);
                                }
                            }
                        }
                    }
                }
                if (dp[i][j][1] == 0) {
                    if (dp[i][j][0] == 2) {
                        dp[i][j][1] = 2;
                        q.emplace(i, j, 1);
                    }
                    else {
                        --d[i][j][1];
                        if (d[i][j][1] == 0) {
                            dp[i][j][1] = 1;
                            q.emplace(i, j, 1);
                        }
                    }
                }
            }
            else {
                // the pre move is mouse
                int mousex = i / m, mousey = i % m, id;
                for (int k = 0; k < 4; ++k) {
                    for (int x = 1; x <= min(mouseJump, dir[i][k] - 1); ++x) {
                        id = f(k, x, mousex, mousey);
                        if (dp[id][j][0] == 0) {
                            if (dp[i][j][1] == 1) {
                                dp[id][j][0] = 1;
                                q.emplace(id, j, 0);
                            }
                            else {
                                --d[id][j][0];
                                if (d[id][j][0] == 0) {
                                    dp[id][j][0] = 2;
                                    q.emplace(id, j, 0);
                                }
                            }
                        }
                    }
                }
                if (dp[i][j][0] == 0) {
                    if (dp[i][j][1] == 1) {
                        dp[i][j][0] = 1;
                        q.emplace(i, j, 0);
                    }
                    else {
                        --d[i][j][0];
                        if (d[i][j][0] == 0) {
                            dp[i][j][0] = 2;
                            q.emplace(i, j, 0);
                        }
                    }
                }
            }
        }
        return dp[mouse][cat][0] == 1;
    }
};