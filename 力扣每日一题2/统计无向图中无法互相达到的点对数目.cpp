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
    long long countPairs(int n, vector<vector<int>>& edges) {
        long long ans = 1ll * n * (n - 1) / 2;

        // construct the union
        UnionFind un(n);
        for (auto& e : edges) 
            un.unite(e[0], e[1]);

        for (int i = 0; i < n; ++i)
            if (un.find(i) == i && un.size[i] >= 2) ans -= 1ll * un.size[i] * (un.size[i] - 1) / 2;
        return ans;
    }
};