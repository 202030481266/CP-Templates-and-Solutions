class Trie {
public:
    vector<Trie*> children;
    bool isEnd;

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
    Trie() : children(26), isEnd(false) {}

    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};
class Encrypter {
    string mp[26];
    unordered_map<string, int> buck;
    Trie* root;
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        int n = keys.size();
        for (int i = 0; i < n; ++i) {
            mp[keys[i] - 'a'] = values[i];
            buck[values[i]] |= (1 << (keys[i] - 'a'));
        }
        this->root = new Trie();
        for (string& v : dictionary) root->insert(v);
    }
    
    string encrypt(string word1) {
        string tmp;
        for (char& ch : word1) {
            tmp.append(mp[ch - 'a']);
        }
        return tmp;
    }

    int dfs(Trie* root, string& s, int p, int n) {
        if (p == 2 * n) {
            return root->isEnd ? 1 : 0;
        }
        string tmp = s.substr(p, 2);
        int x = buck[tmp], res = 0;
        for (int i = 0; i < 26; ++i)
            if ((x & (1 << i)) && root->children[i] != nullptr) res += dfs(root->children[i], s, p + 2, n);
        return res;
    }
    
    int decrypt(string word2) {
        return dfs(root, word2, 0, word2.size() / 2);
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */