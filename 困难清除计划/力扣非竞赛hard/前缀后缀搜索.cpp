// 暴力匹配后缀固然还是超时了
class Trie {
public:
    vector<Trie*> children;
    bool isEnd;
    int index;

    Trie() : children(26), isEnd(false), index(-1) {}

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


    void insert(string word, int idx) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
        node->index = idx;
    }

    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};
class WordFilter {
    unordered_map<string, int> mp;
    Trie* root;
public:
    WordFilter(vector<string>& words) {
        root = new Trie();
        for (int i = 0; i < words.size(); ++i)
            mp[words[i]] = i;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            root->insert(it->first, it->second);
        }
    }
    
    int f(string pref, string suff) {
        // 字典树搜索技术应用
        // 前缀和后缀重叠的情况这时候字符串是固定的

        int n = pref.size(), m = suff.size(), len = min(n, m), ans = -1;
        for (int i = 1; i <= len; ++i) {
            int l = n - i, r = 0;
            while (l < n && pref[l] == suff[r]) ++l, ++r;
            if (l == n) {
                // pref + suff[i : m - 1]
                string tmp;
                if (i == m) tmp = pref; 
                else tmp = pref + suff.substr(i, m - i);
                if (mp.count(tmp)) ans = max(ans, mp[tmp]);
            }
        }

        // 字典树搜索技术
        // 01匹配问题, 字符串的形式为 pref + any + suff
        Trie* start = root->searchPrefix(pref);
        function<void(Trie*, int)> dfs = [&](Trie* root, int match) {
            if (match == m) {
                if (root->isEnd) ans = max(ans, root->index);
                return;
            }
            for (int i = 0; i < 26; ++i) {
                if (root->children[i]) {
                    if (match > 0) {
                        // 已经匹配了第一个后缀字符，那么无论如何都要继续匹配
                        if (suff[match] - 'a' == i) dfs(root->children[i], match + 1);
                    }
                    else {
                        // 还没有开始匹配，那么可以匹配也可以不匹配
                        if (suff[match] - 'a' == i) dfs(root->children[i], match + 1);
                        dfs(root->children[i], match);
                    }
                }
            }
        };
        if (start)
            dfs(start, 0);
        return ans;
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */


// 字典树存储索引的技术，这里的空间复杂度分析我计算错误了
// 实际上所有长度为k的集合总大小最大多为 10^4, 那么字符串的长度最大为 7, 所以两棵字典树的中的坐标空间大小为 1.4 * 10 ^ 5
// 如果空间复杂度分析对了，这道题就会变得十分简单

class WordFilter {
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
    int query(const string& a, const string& b) {
        int n = a.size(), m = b.size();
        auto p = tr1;
        for(int i = 0; i < n; i++) {
            int u = a[i] - 'a';
            if(p->tns[u] == nullptr) return -1;
            p = p->tns[u];
        }
        vector<int>& l1 = p->idxs;
        p = tr2;
        for(int i = m - 1; i >= 0; i--) {
            int u = b[i] - 'a';
            if(p->tns[u] == nullptr) return -1;
            p = p->tns[u];
        }
        vector<int>& l2 = p->idxs;
        n = l1.size(), m = l2.size();
        // 双指针寻找下标
        for(int i = n - 1, j = m - 1; i >= 0 && j >= 0; ) {
            if(l1[i] > l2[j]) i--;
            else if(l1[i] < l2[j]) j--;
            else return l1[i];
        }
        return -1;
    }
    TrieNode* tr1 = new TrieNode, *tr2 = new TrieNode;
    WordFilter(vector<string>& ss) {
        int n = ss.size();
        for(int i = 0; i < n; i++) {
            add(tr1, ss[i], i, false);
            add(tr2, ss[i], i, true);
        }
    }
    
    int f(string a, string b) {
        return query(a, b);
    }
};

