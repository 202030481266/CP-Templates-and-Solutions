class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> a, b;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j]) {
                    a.push_back(i);
                    b.push_back(j);
                }
            }
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        vector<int> sa(a.size() + 1), sb(b.size() + 1);
        for (int i = 0; i < a.size(); ++i)
            sa[i + 1] = sa[i] + a[i];
        for (int i = 0; i < b.size(); ++i)
            sb[i + 1] = sb[i] + b[i];

        int x = 0, y = 0, ans = INT_MAX, N = a.size();

        for (int i = 0; i < n; ++i) {
            while (x < a.size() && a[x] <= i) ++x;
            y = 0;
            for (int j = 0; j < m; ++j) {
                while (y < b.size() && b[y] <= j) ++y;
                // [0, x) is <= i, [0, y) is <= j
                // [0, y) y * j - sb[y - 1] + sb[m] - sb[y - 1] - 
                int sx = sa[N] - 2 * sa[x] + (x * 2 - N) * i;
                int sy = sb[N] - 2 * sb[y] + (y * 2 - N) * j;
                ans = min(ans, sx + sy);
            }
        }
        return ans;
    }
};