#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

// 只能使用搜索类似于一种 s1*s2的模式的字符串，字典树可以做
// 既然如此那么就可以使用两棵字典树进行搜索
// 枚举s1的长度, [0,x],[x+2,n-1]
// 这道题目的O(n*m)传统解法很困难，基本上都是用字符串哈希做的

class Trie {
public:
    unordered_map<int, Trie*> children;
    vector<int> idx;
    Trie* last;
   
    void insert(string& word, int id, bool rev) {
        Trie* node = this;
        for (int i = (rev ? word.size()-1 : 0); (rev ? i >= 0 : i < word.size()); (rev ? --i : ++i)) {
            int ch = word[i] - 'a';
            node->idx.push_back(id);
            if (!node->children.count(ch)) {
                node->children[ch] = new Trie();
            }
            node->children[ch]->last = node;
            node = node->children[ch];
        }
        node->idx.push_back(id);
    }
    Trie* end(string& word) {
        Trie* node = this;
        for (int i = word.size()-1; i > 0; --i) {
            int ch = word[i] - 'a';
            node = node->children[ch];
        }
        return node;
    }
};
class Solution {
public:
    bool differByOne(vector<string>& dict) {
        int n = dict.size(), m = dict[0].size(), dfn[n], s[n];
        Trie* root1 = new Trie(), *root2 = new Trie();
        for (int i = 0; i < n; ++i) {
            root1->insert(dict[i], i, false);
            root2->insert(dict[i], i, true);
        }
        vector<Trie*> q1{root1}, q2;
        for (string& w : dict) q2.push_back(root2->end(w));
        // 枚举前缀长度,1~m-1
        memset(s, 0, sizeof(s));
        for (int i = 0; i < m; ++i) {
            // 前缀和后缀长度始终都是m-1，因为忽略了一个字符
            vector<Trie*> nq1, nq2;
            // 检查layer的节点是否有交集，这里是难点之一
            for (int j = 0; j < q2.size(); ++j) {
                for (int& v : q2[j]->idx) {
                    dfn[v] = j;
                }
                if (q2[j]->last && !s[q2[j]->last->idx[0]]) { // 确保了检查时O(n)
                    nq2.push_back(q2[j]->last);
                    s[q2[j]->last->idx[0]] = 1;
                }
            }
            memset(s, 0, sizeof(s));
            for (auto node : q1) {
                for (int& v : node->idx) {
                    if (s[dfn[v]]) return true;
                    s[dfn[v]] = 1;
                }
                // roll back
                for (int& v : node->idx) {
                    s[dfn[v]] = 0;
                }
                for (auto it = node->children.begin(); it != node->children.end(); ++it) {
                    nq1.push_back(it->second);
                }
            }
            q1 = move(nq1);
            q2 = move(nq2);
        }
        return false;
    }
};




// 在线的字典树解法，实际上这个时间复杂度是O(n*m^2)
class DictTreeNode
{
public:
    vector<DictTreeNode*> nxt;
    bool isend;
    DictTreeNode()
    {
        nxt.resize(26);
        for(int i = 0;i<26;++i)
            nxt[i] = nullptr;
        isend = false;
    }
};

class DictTree
{
    public:
    DictTreeNode* root;

    DictTree()
    {
        root = new DictTreeNode();
    }

    void insert(string &s)
    {  
        DictTreeNode* p = root;
        for(int i=0;i<s.size();++i)
        {
            char c = s[i];
            if(!p->nxt[c-'a'])
            {
                p->nxt[c-'a'] = new DictTreeNode();
            }
            p = p->nxt[c-'a'];
            if(i == s.size()-1) p->isend = true;
        }
    }

    bool find(DictTreeNode* p, string &s, int idx, int dif)
    {
        if(idx==s.size()) return true; 
        if(p->nxt[s[idx]-'a'])
        {
            bool flag = find(p->nxt[s[idx]-'a'], s, idx+1, dif);
            if(flag) return true;
        }
        if(dif)
        {
            for(int i=0;i<26;++i)
            {
                if(!p->nxt[i]) continue;
                if(i==s[idx]-'a') continue;
                bool flag = find(p->nxt[i], s, idx+1, 0);
                if(flag) return true;
            }
        }
        return false;
    }

};

class Solution {
public:
    bool differByOne(vector<string>& dict) {
        DictTree dt;
        for(auto &s:dict)
        {
            if(dt.find(dt.root, s, 0, 1))
                return true;
            dt.insert(s);
        }
        return false;
    }
};