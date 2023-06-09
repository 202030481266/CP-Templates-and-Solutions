struct Trie {
    int val;
    unordered_map<string, Trie*> child; 

    Trie() {
        val = -1;
        child.clear();
    }
};
class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        auto split = [&](string s) {
            vector<string> res;
            string cur;
            for (int i = 1; i < s.size(); ++i) {
                if (s[i] == '/') {
                    res.emplace_back(move(cur));
                    cur.clear();
                } else {
                    cur.push_back(s[i]);
                }
            }
            res.emplace_back(cur);
            return res;
        };
        auto root = new Trie();
        for (int i = 0; i < folder.size(); ++i) {
            auto res = split(folder[i]);
            auto u = root;
            for (auto s : res) {
                if (!u->child.count(s)) {
                    u->child[s] = new Trie();
                }
                u = u->child[s];
            }
            u->val = i;
        }
        vector<string> ans;
        function<void(Trie*)> dfs = [&](Trie* u) {
            if (u->val != -1) {
                ans.emplace_back(folder[u->val]);
                return;
            }
            for (auto&& [_, c] : u->child) {
                dfs(c);
            }
        };
        dfs(root);
        return ans;
    }
};