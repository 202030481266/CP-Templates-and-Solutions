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
    static constexpr int dirs[8][2] = {{1, 0},{-1, 0},{0, 1},{0, -1},{1, 1},{-1, -1},{1, -1}, {-1, 1}};
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        int n = land.size(), m = land[0].size();
        UnionFind un(n * m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (land[i][j]) continue;
                for (int k = 0; k < 8; ++k) {
                    int nx = i + dirs[k][0], ny = j + dirs[k][1];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || land[nx][ny]) continue;
                    un.unite(nx * m + ny, i * m + j);
                }
            }
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (!land[i][j] && un.find(i * m + j) == i * m + j) ans.emplace_back(un.size[i * m + j]); 
        sort(ans.begin(), ans.end());
        return ans;
    }
};