// https://leetcode.cn/problems/graph-connectivity-with-threshold/



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
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
    	// 逆向思维，考虑大于threshold的公因数即可
    	UnionFind un(n + 1);
    	for (int i = threshold + 1; i <= n; ++i) 
    		for (int j = 2; j * i <= n; ++j)
    			un.unite((j - 1) * i, j * i);
    	vector<bool> ans;
    	for (auto &c : queries) ans.emplace_back(un.connected(c[0], c[1]));
    	return ans;
    }
};