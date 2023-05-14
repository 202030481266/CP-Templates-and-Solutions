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
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        UnionFind un(n);
        vector have(n, vector<int>(n));
        vector<int> scc[n];
        for (auto &c : edges) {
            un.unite(c[0], c[1]);
            h[c[0]][c[1]] = h[c[1]][c[0]] = 1;
        }
        for (int i = 0; i < n; ++i) scc[un.find(i)].emplace_back(i);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (scc[i].size()) {
                bool flag = true;
                for (int k = 0; k < scc[i].size(); ++k)
                    for (int x = k + 1; x < scc[i].size(); ++x)
                        if (h[scc[i][k]][scc[i][x]] == 0) flag = false;
                if (flag) ++ans;
            }
        }
        return ans;
    }
};