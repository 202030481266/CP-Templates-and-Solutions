class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        // 思维难题
        // 首先第一步就是使用列交换让每一行变成 “01” 交替的串
        int n = board.size();
        // 下一行要么和前面的行相同要么全部为反
        for (int i = 1; i < n; ++i) {
            bool same = true, contra = true;
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != board[i - 1][j]) same = false;
                if (board[i][j] == board[i - 1][j]) contra = false;
            }
            if (!same && !contra) return -1;
        }
        int sub = (n % 2 == 0 ? 0 : 1);
        int cnt0 = 0, cnt1 = 0, ans = 0;
        // 检查每一行的 1 的数量和 0 的数量
        for (int i = 0; i < n; ++i) {
            if (board[0][i] == 1) ++cnt1;
            else ++cnt0;
        }
        if (abs(cnt1 - cnt0) != sub) return -1;
        if (sub) {
            int c, res;
            if (cnt1 > cnt0) {  // -> 10101
                c = 0, res = 0;
                for (int i = 0; i < n; ++i) {
                    if (board[0][i] == c) ++res;
                    c ^= 1;
                }
            }
            else {
                c = 1, res = 0; // -> 01010
                for (int i = 0; i < n; ++i) {
                    if (board[0][i] == c) ++res;
                    c ^= 1;
                }
            }
            ans += res / 2;
        }
        // 检查每种类型的串，只有两种，称为对偶
        cnt0 = 0, cnt1 = 0;
        for (int i = 0; i < n; ++i) {
            if (board[i][0] == 1) 
                ++cnt1;
            else ++cnt0;
        }
        if (abs(cnt1 - cnt0) != sub) return -1;
        if (sub) {
            int c, res;
            if (cnt1 > cnt0) {
                c = 0, res = 0;
                for (int i = 0; i < n; ++i) {
                    if (board[i][0] == c) ++res;
                    c ^= 1;
                }
            }
            else {
                c = 1, res = 0;
                for (int i = 0; i < n; ++i) {
                    if (board[i][0] == c) ++res;
                    c ^= 1;
                }
            }
            ans += res / 2;
        }
        if (sub == 0) {
            // 决定第一行变为什么类型 0101 还是 1010
            int col1 = 0, col2 = 0, c = 1;
            for (int i = 0; i < n; ++i) {
                if (board[0][i] == c) ++col1;  // -> 0101
                else ++col2;  // -> 1010
                c ^= 1;
            }
            // 决定行变为哪几种 0101 还是 1010
            int row1 = 0, row2 = 0, r = 1;
            for (int i = 0; i < n; ++i) {
                if (board[i][0] == c) ++row1;  // -> 0101
                else ++row2; // -> 1010
                c ^= 1;
            }
            return min(col1, col2) / 2 + min(row1, row2) / 2;
        }
        // 奇数个是会变成固定类型的
        return ans;
    }
};