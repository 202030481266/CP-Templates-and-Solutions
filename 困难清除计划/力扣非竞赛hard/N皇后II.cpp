class Solution {
public:
    int totalNQueens(int n) {
       if (n == 1) return 1;
        vector<bool> col(n), ldiag(2 * n), rdiag(2 * n);

        int ans = 0;

        // dfs
        function<void(int)> dfs = [&](int r) {
            if (r == n) {
                ++ans;
                return;
            }
            for (int i = 0; i < n; ++i) {
                if (col[i] || ldiag[n - r - 1 + i] || rdiag[i + r + 1]) continue;
                col[i] = ldiag[n - r - 1 + i] = rdiag[i + r + 1] = 1;
                dfs(r + 1);
                col[i] = ldiag[n - r - 1 + i] = rdiag[i + r + 1] = 0;
            }
        };

        dfs(0);
        return ans;
    }
};