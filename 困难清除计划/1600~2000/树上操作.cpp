// https://leetcode.cn/problems/operations-on-tree/

// 不超过 2000 次调用, 可以接收o(n)


class LockingTree {
public:
	vector<vector<int>> son;
	vector<int> fa;
	vector<int> status;
	vector<int> tar;

    LockingTree(vector<int>& parent) {
    	int n = parent.size();
    	son.resize(n);
    	fa.resize(n);
        status.resize(n);

    	for (int i = 0; i < n; ++i)
    		fa[i] = parent[i];
    	for (int i = 1; i < n; ++i)
    		son[parent[i]].emplace_back(i);
    }
    
    bool lock(int num, int user) {
        // cerr << "lock" << endl;
    	if (!status[num]) {
    		status[num] = user;
    		return true;
    	}
    	return false;
    }
    
    bool unlock(int num, int user) {
        // cerr << "unlock" << endl;
    	if (!status[num] || status[num] != user) return false;
    	status[num] = 0;
    	return true;
    }

    void dfs(int u) {
    	for (auto v : son[u]) {
    		if (status[v]) tar.emplace_back(v);
    		dfs(v);
    	}
    }
    
    bool upgrade(int num, int user) {
        // cerr << "upgrade" << endl;
    	tar.clear();
    	// check the ancestor
    	bool flag = true;
    	int u = num;
    	while (u != -1) {
    		if (status[u]) {
    			flag = false;
    			break;
    		}
    		u = fa[u];
    	}
    	if (!flag) return false;
    	// check the sons
    	dfs(num);
    	if (tar.size() == 0) return false;
        status[num] = user;
    	for (auto c : tar) status[c] = 0;
    	return true;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */