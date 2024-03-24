// Trie 字典树
// md，用数组被卡成傻逼了
class Trie {
private:
    unordered_map<int, Trie*> children;
    int index, length;

public:
    Trie() : index(-1), length(0) {}

    void insert(string& word, int ind) {
        Trie* node = this;
        int n = word.size();
        for (int i = n - 1; i >= 0; --i) { // 后缀
            int ch = word[i] - 'a';
            if (!node->children.count(ch)) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
            if (node->index == -1) {
                node->index = ind;
                node->length = n;
            }
            else if (node->length > n) {
                node->index = ind;
                node->length = n;
            }
        }
    }

    int get_max_suffix(string& s) {
        Trie* node = this;
        int n = s.size();
        for (int i = n - 1; i >= 0; --i) {
            int ch = s[i] - 'a';
            if (!node->children.count(ch))
                break;
            node = node->children[ch];
        }
        return node->index;
    }

};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int n = wordsContainer.size(), shortest = 0;

        Trie* root = new Trie();
        for (int i = 0; i < n; ++i) {
            root->insert(wordsContainer[i], i);
            if (wordsContainer[i].size() < wordsContainer[shortest].size())
                shortest = i;
        }
        vector<int> ans;
        for (int i = 0; i < wordsQuery.size(); ++i) {
            int res = root->get_max_suffix(wordsQuery[i]);
            ans.push_back(res == -1 ? shortest : res);
        }
    }
};