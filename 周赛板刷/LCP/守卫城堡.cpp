class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int guardCastle(vector<string>& grid) {
        // 此题似乎相当复杂

        /* 
            城堡周围没有传送点
                - 怪物可以到达传送点，那么将所有的传送点变成怪兽，再进行下一步算法
                - 怪物到达不了传送点，那么将所有的传送点转换为墙壁，再进行下一步算法
        */
        /*
            城堡周围有传送点
                - 怪物可以到达传送点，那么将所有的传送点变成城堡，再进行下一步算法
                - 怪物到达不了传送点，那么将所有的传送点转换为墙壁，再进行下一步算法
        */
        /*  
            多城堡和多怪兽算法
                - 寻找最左分割线的贪心算法
                - 如果存在城堡和怪兽接壤，那么本问题无解。
                - 记录最左的城堡或者怪兽，那么可能的情况为
                    - 上下都是城堡，上下都是怪兽
                    - 如果为城堡，上一个位置是最左的城堡：
                        - 更新最左的城堡的位置
                        - 重置分割线判断，重置上下墙壁的位置
                    - 如果为城堡，上一个位置是最左的怪兽：
                        - 位置相邻，问题无解
                        - 如果存在已经满足条件的分割线，ans不变
                        - 存在一个墙壁，ans += 1
                        - ans += 2
                    - 如果为怪兽，上一个位置是最左边的怪兽：
                        - 更新最左边的怪兽的位置
                        - 重置分割线判断，重置上下墙壁的位置
                    - 如果为怪兽，上一个位置是最左边的城堡：
                        - 位置相邻，问题无解
                        - 如果存在已经满足条件的分割线，ans 不变
                        - 存在一个墙壁，ans += 1
                        - ans += 2
                    - 如果为墙壁
                        - 判断不同行的同列，左列是否存在墙壁
                            - 存在，找到分割线
                            - 不存在，找到墙壁
                        - 更新最左上下墙壁的位置
        */
        int n = grid[0].size();
        vector<vector<bool>> vis(2, vector<bool>(n, false));

        // 寻找到城堡的位置
        int x, y;
        for (int i = 0; i < n; ++i) {
            if (grid[0][i] == 'C') x = 0, y = i;
            if (grid[1][i] == 'C') x = 1, y = i;
        }
        // 判断城堡周围有没有城堡
        bool have_p = false;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0], ny = y + dirs[i][1];
            if (nx >= 0 && ny >= 0 && nx < 2 && ny < n && grid[nx][ny] == 'P') have_p = true; 
        }
        // 判断怪兽是否可以到达城堡
        bool arrive_p = false;
        queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            if (grid[0][i] == 'S') q.emplace(0, i), vis[0][i] = true;
            if (grid[1][i] == 'S') q.emplace(1, i), vis[1][i] = true;
        }
        // bfs
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (grid[x][y] == 'P') {
                arrive_p = true;
                break;
            }
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx >= 0 && ny >= 0 && nx < 2 && ny < n && grid[nx][ny] != '#' && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        // 转换图表，此时已经将传送点取消掉
        if (!have_p) {
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < n; ++j) 
                    if (grid[i][j] == 'P') grid[i][j] = (arrive_p ? 'S' : '#'); // 变成怪兽或者是墙壁
        }
        else {
            if (arrive_p) {
                for (int i = 0; i < 2; ++i)
                    for (int j = 0; j < n; ++j)
                        if (grid[i][j] == 'P') grid[i][j] = 'C'; // 变成城堡
            }
            else {
                for (int i = 0; i < 2; ++i)
                    for (int j = 0; j < n; ++j)
                        if (grid[i][j] == 'P') grid[i][j] = '#'; // 变成墙壁
            }
        }

        auto check = [&](int x, int y) -> bool {
            if (grid[x][y] == 'C') {
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && ny >= 0 && nx < 2 && ny < n) {
                        if (grid[nx][ny] == 'S') return false;
                    }
                }
            }
            else {
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    if (nx >= 0 && ny >= 0 && nx < 2 && ny < n) {
                        if (grid[nx][ny] == 'C') return false;
                    }
                }
            }
            return true;
        };

        // cout << grid[0] << endl << grid[1] << endl;

        // 贪心算法
        // 此算法非常复杂繁琐，但是可以证明是最优的算法
        int last_col = -1; // 1 表示城堡， 0 表示怪兽
        int last_up_wall = -1, last_down_wall = -1;
        int have_seg = 0;
        int ans = 0;
        for (int i = 0; i < n; ++i) {

            // cout << i << ' ' << ans << ' ' << last_col << ' ' << last_up_wall << ' ' << last_down_wall << ' ' << endl;
            // 都是平地
            if (grid[0][i] == '.' && grid[1][i] == '.') continue;

            // 上面是墙壁
            if (grid[0][i] == '#') {
                last_up_wall = i;
                if (grid[1][i] == '#' || (i - 1 >= 0 && grid[1][i - 1] == '#')) have_seg = 1;
            }

            // 下面是墙壁
            if (grid[1][i] == '#') {
                last_down_wall = i;
                if (grid[0][i] == '#' || (i - 1 >= 0 && grid[0][i - 1] == '#')) have_seg = 1;
            }

            // 要讨论 6 种情况

            // 双城堡
            if (grid[0][i] == 'C' && grid[1][i] == 'C') {
                if (!check(0, i) || !check(1, i)) return -1;
                if (last_col == -1 || last_col == 1) {
                    last_col = 1;
                    last_up_wall = last_down_wall = -1;
                    have_seg = 0;
                }
                else {
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        if (mx > -1) ans += 1;
                        else ans += 2;
                    }
                    have_seg = 0;
                    last_col = 1;
                    last_up_wall = last_down_wall = -1;
                }
            } 
            // 双怪兽
            else if (grid[0][i] == 'S' && grid[1][i] == 'S') {
                if (!check(0, i) || !check(1, i)) return -1;
                if (last_col == -1 || last_col == 0) {
                    last_col = 0;
                    last_up_wall = last_down_wall = -1;
                    have_seg = 0;
                }
                else {
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        if (mx > -1) ans += 1;
                        else ans += 2;
                    }
                    have_seg = 0;
                    last_col = 0;
                    last_up_wall = last_down_wall = -1;
                }
            }
            // 上城堡
            else if (grid[0][i] == 'C') {
                if (!check(0, i)) return -1;
                if (last_col == -1 || last_col == 1) {
                    last_col = 1;
                    have_seg = 0;
                    last_down_wall = (last_down_wall == i ? i : -1);
                    last_up_wall = -1;
                }
                else {
                    // 没有出现切割线
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        // 此处讨论非常复杂
                        if (mx == -1) {
                            // 表明根本没有任何墙壁
                            ans += 2;
                            last_up_wall = -1;  
                            last_down_wall = i;  // 将下面的变成一个墙壁
                            grid[1][i] = '#';
                        }
                        else {
                            if (mx == last_up_wall) {
                                // 上面的墙壁是最左的
                                if (mx == i - 1) {
                                    // 刚好在左边，那么就可以把右下方给填了
                                    ans += 1;
                                    last_up_wall = -1;
                                    last_down_wall = i;
                                    grid[1][i] = '#';
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                            else {
                                // 下面的墙壁是最左的
                                if (mx == i) {
                                    // 刚好在下面，那么就可以直接填左上角填了
                                    ans += 1;
                                    last_up_wall = -1;
                                    last_down_wall = i;
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            } 
                        }
                    }
                    else {
                        have_seg = 0;
                        last_up_wall = -1;
                        last_down_wall = (last_down_wall == i ? i : -1);
                    }
                    last_col = 1;
                }
            }
            // 下城堡
            else if (grid[1][i] == 'C') {
                if (!check(1, i)) return -1;
                if (last_col == -1 || last_col == 1) {
                    last_col = 1;
                    have_seg = 0;
                    last_down_wall = -1;
                    last_up_wall = (last_up_wall == i ? i : -1);
                }
                else {
                    // 没有切割线
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        if (mx == -1) {
                            // 没有任何的墙壁
                            ans += 2;
                            last_up_wall = i;
                            last_down_wall = -1;
                            grid[0][i] = '#';
                        }
                        else {
                            if (mx == last_down_wall) {
                                if (mx == i - 1) {
                                    // 刚好在左边，那么就可以把右上角填了
                                    ans += 1;
                                    last_up_wall = i;
                                    last_down_wall = -1;
                                    grid[0][i] = '#';
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                            else {
                                if (mx == i) {
                                    // 刚好在上面有一个墙壁，那么就可以把左下角填充了
                                    ans += 1;
                                    last_up_wall = i;
                                    last_down_wall = -1;
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                        }
                    }
                    else {
                        have_seg = 0;
                        last_down_wall = -1;
                        last_up_wall = (last_up_wall == i ? i : -1);
                    }
                    last_col = 1;
                }
            }
            // 上怪兽
            else if (grid[0][i] == 'S') {
                if (!check(0, i)) return -1;
                if (last_col == -1 || last_col == 0) {
                    last_col = 0;
                    have_seg = 0;
                    last_down_wall = (last_down_wall == i ? i : -1);
                    last_up_wall = -1;
                }
                else {
                    // 没有出现切割线
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        // 此处讨论非常复杂
                        if (mx == -1) {
                            // 表明根本没有任何墙壁
                            ans += 2;
                            last_up_wall = -1;  
                            last_down_wall = i;  // 将下面的变成一个墙壁
                            grid[1][i] = '#';
                        }
                        else {
                            if (mx == last_up_wall) {
                                // 上面的墙壁是最左的
                                if (mx == i - 1) {
                                    // 刚好在左边，那么就可以把右下方给填了
                                    ans += 1;
                                    last_up_wall = -1;
                                    last_down_wall = i;
                                    grid[1][i] = '#';
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                            else {
                                // 下面的墙壁是最左的
                                if (mx == i) {
                                    // 刚好在下面，那么就可以直接填左上角填了
                                    ans += 1;
                                    last_up_wall = -1;
                                    last_down_wall = i;
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            } 
                        }
                    }
                    else {
                        have_seg = 0;
                        last_up_wall = -1;
                        last_down_wall = (last_down_wall == i ? i : -1);
                    }
                    last_col = 0;
                }
            }
            // 下怪兽
            else if (grid[1][i] == 'S') {
                if (!check(1, i)) return -1;
                if (last_col == -1 || last_col == 0) {
                    last_col = 0;
                    have_seg = 0;
                    last_down_wall = -1;
                    last_up_wall = (last_up_wall == i ? i : -1);
                }
                else {
                    // 没有切割线
                    if (!have_seg) {
                        int mx = max(last_down_wall, last_up_wall);
                        if (mx == -1) {
                            // 没有任何的墙壁
                            ans += 2;
                            last_up_wall = i;
                            last_down_wall = -1;
                            grid[0][i] = '#';
                        }
                        else {
                            if (mx == last_down_wall) {
                                if (mx == i - 1) {
                                    // 刚好在左边，那么就可以把右上角填了
                                    ans += 1;
                                    last_up_wall = i;
                                    last_down_wall = -1;
                                    grid[0][i] = '#';
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                            else {
                                if (mx == i) {
                                    // 刚好在上面有一个墙壁，那么就可以把左下角填充了
                                    ans += 1;
                                    last_up_wall = i;
                                    last_down_wall = -1;
                                }
                                else {
                                    ans += 1;
                                    last_up_wall = last_down_wall = -1;
                                }
                            }
                        }
                    }
                    else {
                        have_seg = 0;
                        last_down_wall = -1;
                        last_up_wall = (last_up_wall == i ? i : -1);
                    }
                    last_col = 0;
                }
            }
        }

        return ans;
    }
};