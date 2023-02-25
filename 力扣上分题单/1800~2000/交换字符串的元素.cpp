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
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        string ans = s;

        UnionFind un(n);
        for (auto c : pairs) un.unite(c[0], c[1]);

        // group
        vector<int> g[n];
        for (int i = 0; i < n; ++i) {
            g[un.find(i)].emplace_back(i);
        }

        // assign
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i < n; ++i) {
            if (g[i].size() == 0) continue;
            sort(g[i].begin(), g[i].end());
            for (auto c : g[i])
                q.emplace(s[c] - 'a');
            for (auto c : g[i]) {
                ans[c] = char('a' + q.top());
                q.pop();
            }
        }
        return ans;
    }
};