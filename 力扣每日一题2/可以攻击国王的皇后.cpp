class Solution {
    static constexpr int dirs[8][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {1, 1},
        {-1, -1},
        {1, -1},
        {-1, 1}
    };
    int a[10][10];
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<vector<int>> ans;
        for (auto& p : queens) a[p[0]][p[1]] = 1;
        for (int i = 0; i < 8; ++i) {
            int nx = king[0], ny = king[1], flag = 0;
            while (nx >= 0 && ny >= 0 && nx < 8 && ny < 8) {
                if (a[nx][ny]) {
                    flag = 1;
                    break;
                }
                nx += dirs[i][0];
                ny += dirs[i][1];
            }
            if (flag) ans.push_back(vector<int>{nx, ny});
        }
        return ans;
    }
};