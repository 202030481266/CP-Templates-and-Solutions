#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 21;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// cpp被queue卡常数了，只能手写更加好的队列，否则铁定超时
// 使用更紧凑的数据结构
struct State {
    short x, y, e;
    int mask;
    State() = default;
    State(short _x, short _y, int _mask, short _e) : x(_x), y(_y), e(_e), mask(_mask) {}
};

// 静态队列替代STL queue
static State que[6000000];
static int dis[maxn][maxn][1<<10][51];
static int mp[maxn][maxn];

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size(), m = classroom[0].size();
        int sx, sy, tot = 0;
        
        // 快速初始化
        memset(mp, -1, sizeof(mp));
        
        // 找起点和垃圾位置
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (classroom[i][j] == 'S') {
                    sx = i, sy = j;
                } else if (classroom[i][j] == 'L') {
                    mp[i][j] = tot++;
                }
            }
        }
        
        if (tot == 0) return 0;
        
        // 只初始化需要的部分
        const int full_mask = (1 << tot) - 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int mask = 0; mask <= full_mask; ++mask) {
                    for (int e = 0; e <= energy; ++e) {
                        dis[i][j][mask][e] = inf;
                    }
                }
            }
        }
        
        // 静态队列BFS
        int head = 0, tail = 0;
        dis[sx][sy][0][energy] = 0;
        que[tail++] = State(sx, sy, 0, energy);
        
        while (head < tail) {
            State cur = que[head++];
            int x = cur.x, y = cur.y, mask = cur.mask, e = cur.e;
            
            if (e == 0) continue; // 无法移动
            
            // 遍历四个方向
            for (int d = 0; d < 4; ++d) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                
                char cell = classroom[nx][ny];
                if (cell == 'X') continue;
                
                if (cell == 'R') {
                    // 充电站：恢复满能量
                    if (dis[nx][ny][mask][energy] > dis[x][y][mask][e] + 1) {
                        dis[nx][ny][mask][energy] = dis[x][y][mask][e] + 1;
                        que[tail++] = State(nx, ny, mask, energy);
                    }
                } else if (cell == 'L') {
                    // 垃圾：收集垃圾，消耗能量
                    int new_mask = mask | (1 << mp[nx][ny]);
                    int new_e = e - 1;
                    if (dis[nx][ny][new_mask][new_e] > dis[x][y][mask][e] + 1) {
                        dis[nx][ny][new_mask][new_e] = dis[x][y][mask][e] + 1;
                        que[tail++] = State(nx, ny, new_mask, new_e);
                    }
                } else {
                    // 空地：消耗能量
                    int new_e = e - 1;
                    if (dis[nx][ny][mask][new_e] > dis[x][y][mask][e] + 1) {
                        dis[nx][ny][mask][new_e] = dis[x][y][mask][e] + 1;
                        que[tail++] = State(nx, ny, mask, new_e);
                    }
                }
            }
        }
        
        // 寻找答案：在任意垃圾位置收集完所有垃圾
        int ans = inf;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (classroom[i][j] == 'L') {
                    for (int e = 0; e <= energy; ++e) {
                        ans = min(ans, dis[i][j][full_mask][e]);
                    }
                }
            }
        }
        
        return ans == inf ? -1 : ans;
    }
};

// 常数更加好的版本
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        vector idx(m, vector<int>(n));
        int cnt_l = 0, sx = 0, sy = 0;
        for (int i = 0; i < m; i++) {
            const string& row = classroom[i];
            for (int j = 0; j < n; j++) {
                char b = row[j];
                if (b == 'L') {
                    idx[i][j] = cnt_l++; // 给垃圾分配编号
                } else if (b == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        int u = 1 << cnt_l;
        vector vis(m, vector(n, vector(energy + 1, vector<int8_t>(u))));
        vis[sx][sy][energy][u - 1] = true;
        struct Node { int x, y, e, mask; };
        vector<Node> q = {{sx, sy, energy, u - 1}};
        for (int ans = 0; !q.empty(); ans++) {
            auto tmp = q;
            q.clear();
            for (auto& [x, y, e, mask] : tmp) {
                if (mask == 0) { // 所有垃圾清理完毕
                    return ans;
                }
                if (e == 0) { // 走不动了
                    continue;
                }
                for (auto& [dx, dy] : dirs) {
                    int nx = x + dx, ny = y + dy;
                    if (0 <= nx && nx < m && 0 <= ny && ny < n && classroom[nx][ny] != 'X') {
                        int new_e = classroom[nx][ny] == 'R' ? energy : e - 1;
                        int new_mask = classroom[nx][ny] == 'L' ? mask & ~(1 << idx[nx][ny]) : mask;
                        if (!vis[nx][ny][new_e][new_mask]) {
                            vis[nx][ny][new_e][new_mask] = true;
                            q.emplace_back(nx, ny, new_e, new_mask);
                        }
                    }
                }
            }
        }
        return -1;
    }
};


// 优化状态的版本 （剪枝，跑的飞快）
// 贪心的最优解剪枝，也就是说如果 nx, ny, mask的这个状态下 e1 已经被搜索过了，那么所有的 小于 e1 的 nx, ny, mask肯定不用搜索了
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        vector idx(m, vector<int>(n));
        int cnt_l = 0, sx = 0, sy = 0;
        for (int i = 0; i < m; i++) {
            const string& row = classroom[i];
            for (int j = 0; j < n; j++) {
                char b = row[j];
                if (b == 'L') {
                    idx[i][j] = cnt_l++; // 给垃圾分配编号
                } else if (b == 'S') {
                    sx = i;
                    sy = j;
                }
            }
        }

        int u = 1 << cnt_l;
        vector max_energy(m, vector(n, vector<int8_t>(u, -1)));
        max_energy[sx][sy][u - 1] = energy; 
        struct Node { int x, y, e, mask; };
        vector<Node> q = {{sx, sy, energy, u - 1}};

        for (int ans = 0; !q.empty(); ans++) {
            auto tmp = q;
            q.clear();
            for (auto& [x, y, e, mask] : tmp) {
                if (mask == 0) { // 所有垃圾清理完毕
                    return ans;
                }
                if (e == 0) { // 走不动了
                    continue;
                }
                for (auto& [dx, dy] : dirs) {
                    int nx = x + dx, ny = y + dy;
                    if (0 <= nx && nx < m && 0 <= ny && ny < n && classroom[nx][ny] != 'X') {
                        int new_e = classroom[nx][ny] == 'R' ? energy : e - 1;
                        int new_mask = classroom[nx][ny] == 'L' ? mask & ~(1 << idx[nx][ny]) : mask;
                        if (new_e > max_energy[nx][ny][new_mask]) {
                            max_energy[nx][ny][new_mask] = new_e;
                            q.emplace_back(nx, ny, new_e, new_mask);
                        }
                    }
                }
            }
        }
        return -1;
    }
};