class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>> &grid) {
        unordered_map<int, int> idx;
        for (int i = 0; i < grid.size(); i++) {
            int mask = 0;
            for (int j = 0; j < grid[i].size(); j++)
                mask |= grid[i][j] << j;
            idx[mask] = i;
        }
        if (idx.count(0)) return {idx[0]};
        for (auto [x, i]: idx)
            for (auto [y, j]: idx)
                if ((x & y) == 0)
                    return {min(i, j), max(i, j)};
        return {};
    }
};

