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
    int minScore(int n, vector<vector<int>>& roads) {
        vector<int> dis(n + 1, INT_MAX);
        auto ds = UnionFind(n + 1);
        for (auto c : roads) {
            if (!ds.connected(c[0], c[1])) {
                int t = ds.find(c[0]), tt = ds.find(c[1]);
                ds.unite(c[0], c[1]);
                int x = ds.find(c[0]);
                dis[x] = min({dis[x], dis[tt], dis[t], c[2]});
            } else {
                int t = ds.find(c[0]);
                dis[t] = min(dis[t], c[2]);
            }
        }
        return dis[ds.find(n)];
    }
};