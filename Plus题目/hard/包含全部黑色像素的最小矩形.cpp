class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        int n = image.size(), m = image[0].size();

        auto check_col = [&](int col) -> bool {
            for (int i = 0; i < n; ++i)
                if (image[i][col]=='1') return true;
            return false;
        };
        auto check_row = [&](int row) -> bool {
            for (int i = 0; i < m; ++i)  
                if (image[row][i]=='1') return true;
            return false;
        };

        auto get = [&](int type, int f, int l, int r) -> int {
            if (type == 1) { // 找最大的
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    bool res = (f ? check_row(mid) : check_col(mid));
                    if (res) l = mid;
                    else r = mid;
                }
                return l;
            }
            else {
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    bool res = (f ? check_row(mid) : check_col(mid));
                    if (res) r = mid;
                    else l = mid;
                }
                return r;
            }
        };

        int up, down, left, right;

        up = get(0, 1, -1, x);// 找到最小的有黑像素的边
        down = get(1, 1, x, n); // 找到最大的有黑像素的边
        left = get(0, 0, -1, y); // 找到最小的有黑像素的边
        right = get(1, 0, y, m); // 找到最大的有黑像素的边

        return (right - left + 1) * (down - up + 1);
    }

};