// https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/



class TreeAncestor {
public:
	vector<vector<int>> f;
	vector<vector<int>> g;
	vector<int> dep;
	int N;

	void dfs(int u, int father) {
		dep[u] = dep[father] + 1;
		f[u][0] = father;
		for (int i = 1; i <= 20; ++i)
			f[u][i] = f[f[u][i - 1]][i - 1];  // 倍增求解k级LCA
		for (int v : g[u])
			if (v != father) dfs(v, u);
	}

    TreeAncestor(int n, vector<int>& parent) {
			N = n;
    	f = vector(n + 1, vector<int>(21));
    	g.resize(n + 1);
    	dep.resize(n + 1);
    	fill(dep.begin(), dep.end(), 0);
    	for (int i = 1; i < n; ++i) {
    		g[i].emplace_back(parent[i]);
    		g[parent[i]].emplace_back(i);
    	}
    	dfs(0, n);
    }
    
    int getKthAncestor(int node, int k) {
    	int t = dep[node] - k;
			if (t <= 0) return -1;
    	for (int i = 20; i >= 0; --i) {
    		if (dep[f[node][i]] > t) node = f[node][i];
    	}
    	return f[node][0];
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */