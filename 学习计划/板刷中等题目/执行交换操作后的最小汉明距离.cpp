class UnionFind {
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
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        UnionFind un(n);
        for (auto& e : allowedSwaps) {
            int x = e[0], y = e[1];
            un.unite(x, y);
        }
        vector<int> vis(n, -1);
        int m = 0;
        for (int i = 0; i < n; ++i) {
            int f = un.find(i);
            if (vis[f] < 0) {
                vis[f] = m++;
            }
        }
        vector<int> g[m];
        for (int i = 0; i < n; ++i) {
            g[vis[un.find(i)]].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < m; ++i){
            unordered_map<int, int> cnt;
            for (int p : g[i]) ++cnt[source[p]];
            for (int p : g[i]) {
                if (cnt.count(target[p]) && cnt[target[p]] > 0)
                    --cnt[target[p]];
            }
            for (auto& [k, v] : cnt)
                ans += v;
        }
        return ans;
    }
};