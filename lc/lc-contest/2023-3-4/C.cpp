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
    static constexpr int mod = 1000000007;
    int pow_mod(int x, int n) {
        int res = 1;
        for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
            if ((n & 1) != 0)
                res = (int)(res * p % mod);
        return res;
    }
    int countWays(vector<vector<int>>& ranges) {
        int n = ranges.size();

        sort(ranges.begin(), ranges.end(), [&](const vector<int>& a, const vector<int>& b){
            return (a[0] != b[0]) ? a[0] < b[0] : a[1] < b[1];
        });

        UnionFind un(n);
        for (int i = 0; i < n; ++i) {
            int j = i + 1, mx = ranges[i][1];
            while (j < n && ranges[j][0] <= mx) {
                un.unite(i, j);
                mx = max(mx, ranges[j++][1]);
            }
            i = j - 1;
        }
        int res = 0;
        for (int i = 0; i < n; ++i)
            if (un.find(i) == i) ++res;
        return pow_mod(2, res);
    }
};