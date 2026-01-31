typedef long long ll;
typedef pair<int, int> pii;
class Solution {
    static constexpr ll M = 1e9;
public:
    string gobang(vector<vector<int>>& pieces) {
        set<pii> black;
        set<pii> white;

        for (auto& p : pieces) {
            if (p[2]) {
                // white position
                white.emplace(p[0], p[1]);
            }
            else {
                black.emplace(p[0], p[1]);
            }
        }

        auto exist = [&](int x, int y, int type) -> bool {
            if (type) return white.find({x, y}) != white.end();
            else return black.find({x, y}) != black.end();
        };

        int dirs[8][2] = {
            {0, -1}, {0, 1}, 
            {-1, 0}, {1, 0},
            {-1, -1}, {1, 1},
            {1, -1}, {-1, 1}
        };

        auto check_one_step_win = [&](int x, int y, int type) -> bool {
            // 检查是否可以造成一步胜利
            // 如果能够造成胜利，那么在其中4个方向中至少有一个方向出现了5个棋子
            int l1 = 0, l2 = 0, x_offset = 0, y_offset = 0;  
            for (int i = 0; i < 8; i += 2) {
                l1 = 0;
                l2 = 0;
                x_offset = dirs[i][0];
                y_offset = dirs[i][1];
                while (exist(x + x_offset, y + y_offset, type)) {
                    x_offset += dirs[i][0];
                    y_offset += dirs[i][1];
                    ++l1;
                }
                x_offset = dirs[i + 1][0];
                y_offset = dirs[i + 1][1];
                while (exist(x + x_offset, y + y_offset, type)) {
                    x_offset += dirs[i + 1][0];
                    y_offset += dirs[i + 1][1];
                    ++l2;
                }
                if (l1 + l2 >= 4) {
                    // 构成了五个五子棋
                    return true;
                }
            }
            return false;
        };

        set<pii> black_vis, white_vis;
        for (auto it = black.begin(); it != black.end(); ++it) {
            int x = it->first, y = it->second;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (exist(nx, ny, 0) || exist(nx, ny, 1) || black_vis.find({nx, ny}) != black_vis.end()) continue; // 已经存在了棋子
                black_vis.emplace(nx, ny);
                if (check_one_step_win(nx, ny, 0)) {
                    return "Black";
                }
            }
        }

        int white_one_step_win = 0, win_x, win_y;
        for (auto it = white.begin(); it != white.end(); ++it) {
            int x = it->first, y = it->second; 
            for (int i = 0; i < 8; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (exist(nx, ny, 0) || exist(nx, ny, 1) || white_vis.find({nx, ny}) != white_vis.end()) continue;
                white_vis.emplace(nx, ny);
                if (check_one_step_win(nx, ny, 1)) {
                    ++white_one_step_win;
                    win_x = nx, win_y = ny;
                    if (white_one_step_win > 1) return "White";
                }
            }
        }

        // 现在检查一个棋子对于整个黑色棋局的变化贡献
        // 即，检查该棋子能够创造出多少的一步制胜的位置
        auto calculate = [&](int x, int y) -> int {
            int l1_no_skip = 0, l1_one_skip = 0;
            int l2_no_skip = 0, l2_one_skip = 0;
            int x_offset, y_offset;
            int res = 0;
            for (int i = 0; i < 8; i += 2) {
                l1_no_skip = 0, l1_one_skip = 0;
                l2_no_skip = 0, l2_one_skip = 0;
                x_offset = dirs[i][0], y_offset = dirs[i][1];
                while (exist(x + x_offset, y + y_offset, 0)) {
                    x_offset += dirs[i][0];
                    y_offset += dirs[i][1];
                    ++l1_no_skip;
                    ++l1_one_skip;
                }
                // 检查是否为白色的棋子
                if (!exist(x + x_offset, y + y_offset, 1)) {
                    ++l1_one_skip;
                    x_offset += dirs[i][0];
                    y_offset += dirs[i][1];
                    while (exist(x + x_offset, y + y_offset, 0)) {
                        x_offset += dirs[i][0];
                        y_offset += dirs[i][1];
                        ++l1_one_skip;
                    }
                }
                x_offset = dirs[i + 1][0], y_offset = dirs[i + 1][1];
                while (exist(x + x_offset, y + y_offset, 0)) {
                    x_offset += dirs[i + 1][0];
                    y_offset += dirs[i + 1][1];
                    ++l2_no_skip;
                    ++l2_one_skip;
                }
                // 检查是否为白色的棋子
                if (!exist(x + x_offset, y + y_offset, 1)) {
                    ++l2_one_skip;
                    x_offset += dirs[i + 1][0];
                    y_offset += dirs[i + 1][1];
                    while (exist(x + x_offset, y + y_offset, 0)) {
                        x_offset += dirs[i + 1][0];
                        y_offset += dirs[i + 1][1];
                        ++l2_one_skip;
                    }
                }
                // cout << l1_no_skip << ' ' << l1_one_skip << ' ' << l2_no_skip << ' ' << l2_one_skip << endl;
                // 注意这里必须要有一个可以填空的地方才能增加结果
                if (l1_one_skip + l2_no_skip + 1 >= 5 && l1_one_skip > l1_no_skip) ++res;
                if (l2_one_skip + l1_no_skip + 1 >= 5 && l2_one_skip > l2_no_skip) ++res;
            }
            return res;
        };

        // calculate(1, 3);

        // 如果白色的棋子存在一步制胜，那么黑色棋子必然在第一步会封杀该局势
        // 所以唯一会让黑色的棋子赢的方法在于该封杀恰好造成了必赢局
        if (white_one_step_win) {
            int choice = calculate(win_x, win_y);
            return (choice > 1 ? "Black" : "None");
        }

        // 如果白色没有一步制胜的棋子，那么白色棋子不可能赢，所以黑色第一步就是寻找到最大贡献的位置
        // 那么其中的候选位置必然是有两种，枚举所有已经存在的点，那么候选的点就是相邻的八个方向的点以及可以跳过
        set<pii> vis(black_vis);
        for (auto it = black_vis.begin(); it != black_vis.end(); ++it) {
            int x = it->first, y = it->second;
            if (calculate(x, y) > 1) {
                return "Black";
            }
            for (int d = 0; d < 8; ++d) {
                int nx = x + dirs[d][0], ny = y + dirs[d][1];
                if (exist(nx, ny, 0) || exist(nx, ny, 1) || vis.find({nx, ny}) != vis.end()) continue;
                vis.emplace(nx, ny);
                if (calculate(nx, ny) > 1) {
                    return "Black";
                }
            }
        }
        return "None";
    } 
};