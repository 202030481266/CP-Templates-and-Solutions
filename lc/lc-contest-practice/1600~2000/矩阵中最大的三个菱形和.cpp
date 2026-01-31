// 枚举
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        auto cal = [&](int x, int y, int len) -> int {
            int sum = 0, c = (len - 1) / 2, l, r, i;
            for (i = x, l = y + c, r = l; i <= x + c; ++i, --l, ++r)
                sum += (l == r ? grid[i][l] : grid[i][l] + grid[i][r]);
            for (i = x + len - 1, l = y + c, r = l; i > x + c; --i, --l, ++r)
                sum += (l == r ? grid[i][l] : grid[i][l] + grid[i][r]);
            return sum;
        };

        set<int> s;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) 
                for (int len = 1; i + len - 1 < n && j + len - 1 < m; len += 2) {
                    int res = cal(i, j, len);
                    s.insert(res);
                    if (s.size() > 3) s.erase(s.begin());
                }
        vector<int> ans;
        // 反向迭代器
        for (auto it = s.rbegin(); it != s.rend(); ++it)
            ans.push_back(*it);
        return ans;
    }
};