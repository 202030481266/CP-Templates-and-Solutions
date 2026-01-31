class UnionFind {
public:
    vector<int> parent, size;
    int n, setCount;
public:
    UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        --setCount;
        return true;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
class Solution {
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int findMaxFish(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionFind un(n * m);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) 
                if (grid[i][j] > 0) {
                    for (int k = 0; k < 4; ++k) {
                        int nx = i + dirs[k][0], ny = j + dirs[k][1];
                        if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == 0) continue;
                        un.unite(i * m + j, nx * m + ny);
                    }
                }
        vector<int> res(n * m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] > 0)
                    res[un.find(i * m + j)] += grid[i][j];
        return *max_element(res.begin(), res.end());
    }
};