// https://leetcode.cn/problems/minimize-malware-spread/



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
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    	int n = graph.size();

    	UnionFind un(n);

    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < n; ++j)
    			if (graph[i][j]) un.unite(i, j);

    	int mx = INT_MIN, ans = 0, mn = INT_MAX;
    	vector<int> a(n);
    	for (auto c : initial) {
    		++a[un.find(c)];
    	}
    	bool flag = false;  // means there is no 1 set
    	for (auto c : initial) {
    		int fa = un.find(c);
    		if (a[fa] == 1) {
    			flag = true;
    			if (un.size[fa] > mx || (un.size[fa] == mx && c < ans))
    				mx = un.size[fa], ans = c;
    		}
    		mn = min(mn, c);
    	}
    	return flag ? ans : mn;
    }
};