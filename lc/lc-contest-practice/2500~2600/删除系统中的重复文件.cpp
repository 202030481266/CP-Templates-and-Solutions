struct Node {
    string str;
    unordered_map<string, Node*> children;
    Node(string x): str(x) {}
}; // 字典树
class Solution {
    unordered_map<Node*, bool> del;
    unordered_map<string, Node*> exi;
    Node* root;
    vector<vector<string>> ans;
    vector<string> res;
public:
    string dfs(Node* root) {
        if (!root) return "";
        string serial;
        vector<string> childrenString;
        for (auto &child : root->children)
            childrenString.emplace_back(child.first + "(" + dfs(child.second)+ ")");
        sort(childrenString.begin(), childrenString.end());
        for (auto s : childrenString) serial += s;
        if (serial.size()) { // 非空
            if (exi.count(serial)) { 
                del[root] = 1;
                del[exi[serial]] = 1;
            }
            else exi[serial] = root;
        }
        return root->str + "(" + serial + ")";
    }
    void add(Node* f, vector<string>& s) {
        for (int i = 0; i < s.size() - 1; ++i) f = f->children[s[i]];
        Node* tmp = new Node(s.back());
        f->children[s.back()] = tmp; 
    }
    void sol(Node* root) {
        for (auto& child : root->children) {
            if (!del[child.second]) {
                res.emplace_back(child.first);
                ans.emplace_back(res);
                sol(child.second);
                res.pop_back();
            }
        }
    }
    vector<vector<string>>  deleteDuplicateFolder(vector<vector<string>>& paths) {
        root = new Node("/");
        sort(paths.begin(), paths.end(), [&](vector<string>& a, vector<string>& b){
            return a.size() < b.size();
        });
        for (auto& s : paths) add(root, s);
        dfs(root);
        sol(root);
        return ans;
    }
};