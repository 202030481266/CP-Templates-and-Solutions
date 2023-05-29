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
    bool canTraverseAllPairs(vector<int>& nums) {
        vector<int> pos(100010);
        sort(nums.begin(), nums.end());
        if (nums.size() == 1) return true;
        int mx = nums.back();
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; ++i) pos[nums[i]] = i + 1;
        if (pos[1] > 0) return false;  // 全是1
        UnionFind un(n + 1);
        for (int i = 2; i <= mx; ++i) {
            int f = -1;
            for (int j = i; j <= mx; j += i) {
                if (pos[j] > 0) {
                    if (f == -1) f = pos[j];
                    else un.unite(pos[j], f);
                }
            }
        }
        int f = un.find(1);
        for (int i = 2; i <= n; ++i)
            if (un.find(i) != f) return false;
        return true;
    }
};