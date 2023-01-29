// 动态维护字符流，然后判断后缀
// 技巧：使用字典树来维护即可，对于字典的后缀反向构建字典树

typedef long long ll;
#define RF(i, begin, end) for (ll i = begin; i >= end; --i)


struct TrieNode
{
    TrieNode *children[26];
    bool isEnd;
};

class Trie
{
public:
    TrieNode * root;
    Trie(){
        root = new TrieNode();
        memset(root->children, 0, sizeof(root->children));
        root->isEnd = false;
    }

    void insert(const string& s){
        TrieNode *tmp = root;
        RF(i, s.size() - 1, 0)
        {
            if(not tmp->children[s[i] - 'a'])
                tmp->children[s[i] - 'a'] = new TrieNode();
            tmp = tmp->children[s[i] - 'a'];
        }
        tmp->isEnd = true;
    }
    bool startswith(const string& s)
    {
        TrieNode *tmp = root;
        RF(i, s.size() - 1, 0)
        {
            if(not tmp->children[s[i]- 'a'])
                break;
            tmp = tmp->children[s[i] - 'a'];
            if(tmp->isEnd)
                return true;
        }
        return false;
    }
};

class StreamChecker {
public:
    Trie trie;
    string s;
    StreamChecker(vector<string>& words) {
        for(const auto &w : words){
            trie.insert(w);
        }
    }
    bool query(char letter) {
        s.push_back(letter);            // 对于流中的字母用 string 保存
        return trie.startswith(s);      // 每次新来一个字符，就逆序遍历
    }
};


/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */

