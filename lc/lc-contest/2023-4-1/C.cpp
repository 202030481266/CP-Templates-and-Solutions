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
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size();

        vector<vector<int>> a(n);
        UnionFind un(n);

        for (int i = 0; i < n; ++i) {
            un.unite(i, (i + k) % n);
        }
        for (int i = 0; i < n; ++i) {
            a[un.find(i)].emplace_back(arr[i]);
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i].size()) {
                nth_element(a[i].begin(), a[i].begin() + a[i].size() / 2, a[i].end());
                int mid = a[i][a[i].size() / 2];
                for (int v : a[i]) ans += abs(v - mid);
            }
        }
        return ans;
    }
};