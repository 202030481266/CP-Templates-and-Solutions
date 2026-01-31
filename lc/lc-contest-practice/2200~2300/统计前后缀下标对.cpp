// 暴力字典树，超时
class Solution {
public:
    struct TrieNode {
        TrieNode* tns[26] {nullptr};
        vector<int> idxs;
    };
    void add(TrieNode* p, const string& s, int idx, bool isTurn) {
        int n = s.size();
        p->idxs.push_back(idx);
        for(int i = isTurn ? n - 1 : 0; i >= 0 && i < n; i += isTurn ? -1 : 1) {
            int u = s[i] - 'a';
            if(p->tns[u] == nullptr) p->tns[u] = new TrieNode();
            p = p->tns[u];
            p->idxs.push_back(idx);
        }
    }
    int get(const string& s) {
        int n = s.size();
        auto p = tr1;
        for (int i = 0; i < n; ++i) {
            int u = s[i] - 'a';
            if (p->tns[u] == nullptr) return 0;
            p = p->tns[u];
        }
        vector<int>& l1 = p->idxs;
        p = tr2;
        for (int i = n - 1; i >= 0; --i) {
            int u = s[i] - 'a';
            if (p->tns[u] == nullptr) return 0;
            p = p->tns[u];
        }
        vector<int>& l2 = p->idxs;
        int m1 = l1.size(), m2 = l2.size(), res = 0;
        int i = m1 - 1, j = m2 - 1;
        while (i >= 0 && j >= 0) {
            if (l1[i] < l2[j]) --i;
            else if (l1[i] > l2[j]) --j;
            else {
                ++res;
                --i;
                --j;
            }
        }
        return res;
    }
    TrieNode* tr1 = new TrieNode, *tr2 = new TrieNode;
    long long countPrefixSuffixPairs(vector<string>& words) {
        // 745 前缀和后缀搜索
        int n = words.size(), ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            ans += get(words[i]);
            add(tr1, words[i], i, false);
            add(tr2, words[i], i, true);
        }
        return ans;
    }
};


// 字典树的另一种技巧做法
class Solution {
public:
    struct Trie {
        unordered_map<int, Trie*> childs;
        int cnt = 0;
    };
    Trie* trie = new Trie();
    void add(const string& s) {
        Trie* cur = trie;
        int n = s.size();
        for (int i = 0, j = n - 1; i < n; ++i, --j) {
            int idx = (s[i] - 'a') * 26 + (s[j] - 'a');
            if (!cur->childs.count(idx)) {
                cur->childs[idx] = new Trie();
            }
            cur = cur->childs[idx];
            cur->cnt += 1;
        }
    }
    int query(const string& s) {
        Trie* cur = trie;
        int n = s.size();
        for (int i = 0, j = n - 1; i < n; ++i, --j) {
            int idx = (s[i] - 'a') * 26 + (s[j] - 'a');
            if (!cur->childs.count(idx)) return 0;
            cur = cur->childs[idx];
        }
        return cur->cnt;
    }
    long long countPrefixSuffixPairs(vector<string>& words) {
        // 745 前缀和后缀搜索是一道更加难的问题，因为前缀和后缀长度还不相同
        int n = words.size();
        long long ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            ans += query(words[i]);
            add(words[i]);
        }
        return ans;
    }
};

