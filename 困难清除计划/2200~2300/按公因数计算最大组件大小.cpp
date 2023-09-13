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
    int a[100010];
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        UnionFind un(100001);
        for (int& v : nums) a[v] = 1;
        for (int i = 2; i <= 100000; ++i) {
            int pre = -1;
            for (int j = i; j <= 100000; j += i) {
                if (a[j]) {
                    if (pre == -1) pre = j;
                    else un.unite(pre, j);
                }
            }
        }
        memset(a, 0, sizeof(a));
        for (int& v : nums) ++a[un.find(v)];
        return *max_element(a, a + 100010);
    }
};