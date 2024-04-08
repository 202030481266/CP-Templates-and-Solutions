class ThroneInheritance {
public:

    unordered_map<string, vector<string>> tree;
    unordered_set<string> dead;

    string root;

    ThroneInheritance(string kingName) {
        root = kingName;
    }
    
    void birth(string parentName, string childName) {
        tree[parentName].push_back(childName);
    }
    
    void death(string name) {
        dead.insert(name);
    }

    void dfs(string cur, vector<string>& order) {
        if (!dead.count(cur)) 
            order.push_back(cur);
        for (string& s : tree[cur]) {
            dfs(s, order);
        }
    }

    vector<string> getInheritanceOrder() {
        vector<string> ans;
        dfs(root, ans);
        return ans;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */