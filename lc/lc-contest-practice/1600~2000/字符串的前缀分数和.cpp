// 卡了内存空间的限制，使用unordered_map可以卡过去了，但是常数巨大
// 这道题的最佳方法应该就是字典树， O(L) 建树（遍历所有的字符串一次 + O(L) 扫描答案（也是遍历了所有字符串一次）
class Trie {
public:
    unordered_map<int, Trie*> children;
    int cnt = 0;
    int searchPrefix(string prefix) {
        Trie* node = this;
        int res = 0;
        for (char ch : prefix) {
            ch -= 'a';
            node = node->children[ch];
            res += node->cnt;
        }
        return res;
    }
    Trie() {}
    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children.count(ch) == 0) node->children[ch] = new Trie();
            node = node->children[ch];
        }
        node->cnt += 1;
    }
};
class Solution {
public:
    int dfs(Trie* node) {
        int res = 0;
        for (auto [k, v] : node->children) {
            res += dfs(v);
        }
        node->cnt += res;
        return node->cnt;
    }
    vector<int> sumPrefixScores(vector<string>& words) {
        int n = words.size();
        Trie* root = new Trie();
        for (string& s : words) root->insert(s);
        dfs(root);
        vector<int> ans;
        for (string& s : words) {
            ans.push_back(root->searchPrefix(s));
        }
        return ans;
    }
};