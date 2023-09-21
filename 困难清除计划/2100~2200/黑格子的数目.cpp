class Solution {
    unordered_map<long long, long long> h;
public:
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        for (auto& p : coordinates) {
            long long x = p[0], y = p[1];
            if (x - 1 >= 0 && y - 1 >= 0) ++h[(x - 1) * n + y - 1];
            if (x + 1 < m && y - 1 >= 0) ++h[x * n + y - 1];
            if (x - 1 >= 0 && y + 1 < n) ++h[(x - 1) * n + y];
            if (x + 1 < m && y + 1 < n) ++h[x * n + y];
        }
        vector<long long> ans(5);
        long long tot = 0;
        for (auto [u, v] : h) {
            ++ans[v];
            ++tot;
        }
        ans[0] = 1ll * (m - 1) * (n - 1) - tot;
        return ans;
    }
};