// https://leetcode.cn/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/



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
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
    	vector<vector<int>> blue;
    	vector<vector<int>> red;
    	vector<vector<int>> green;

    	for (auto c : edges) {
    		if (c[0] == 1) red.emplace_back(c);
    		else if (c[0] == 2) green.emplace_back(c);
    		else blue.emplace_back(c);
    	}

    	// 首先使用蓝边来构建图，并且剔除掉多余的蓝色边
    	int ans = 0;
    	UnionFind un(n + 1);
    	for (auto c : blue) {
    		if (un.connected(c[1], c[2])) {
    			++ans;
    			continue;
    		}
    		un.unite(c[1], c[2]);
    	}
    	// 检查是否需要使用特定的边，因为对于Alice和Bob来说，特定类型的边并不影响他们，只会影响自己
    	UnionFind alice(un);
    	UnionFind bob(un);

    	// alice
    	for (auto c : red) {
    		if (alice.connected(c[1], c[2])) {
    			++ans;
    			continue;
    		}
    		alice.unite(c[1], c[2]);
    	}
    	// bob
    	for (auto c : green) {
    		if (bob.connected(c[1], c[2])) {
    			++ans;
    			continue;
    		}
    		bob.unite(c[1], c[2]);
    	}
    	// 检查是否能够连通所有的点
    	int a = 0, b = 0;
    	for (int i = 1; i <= n; ++i) if (alice.find(i) == i) ++a;
    	for (int i = 1; i <= n; ++i) if (bob.find(i) == i) ++b;
    	if (a > 1 || b > 1) return -1;
    	return ans;
    }
};