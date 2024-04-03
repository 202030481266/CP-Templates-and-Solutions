class Trie {
public:
    vector<Trie*> children;
    vector<int> index;

    Trie* searchPrefix(string prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }
    
    Trie() : children(26) {}

    void insert(string word, int ind) {
        Trie* node = this;
        node->index.push_back(ind);
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
            node->index.push_back(ind);
        }
    }

    Trie* get(string prefix) {
        return searchPrefix(prefix);
    }
};
class Solution {
public:
    // 字典树优化查询
    vector<vector<string>> wordSquares(vector<string>& words) {
        int n = words.size(), m = words[0].size();
        Trie* root = new Trie();
        for (int i = 0; i < n; ++i) {
            root->insert(words[i], i);
        }

        vector<int> cur;
        vector<vector<string>> ans;

        function<void(int)> dfs = [&](int p) {
            if (p == m) {
                vector<string> res;
                for (int& v : cur)
                    res.push_back(words[v]);
                ans.push_back(res);
                return;
            }
            string prefix;
            for (int i = 0; i < p; ++i)
                prefix.push_back(words[cur[i]][p]);
            Trie* tmp = root->get(prefix);
            if (tmp)
                for (int& v : tmp->index) {
                    cur.push_back(v);
                    dfs(p + 1);
                    cur.pop_back();
                } 
        };
        dfs(0);
        return ans;
    }
};