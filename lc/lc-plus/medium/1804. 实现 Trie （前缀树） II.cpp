#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Trie {
public:
    vector<Trie*> children;
    int val;
    int w;

    Trie():children(26), val(0), w(0) {}
    
    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node->w++; // path weight
            node = node->children[ch];
        }
        node->w++;
        node->val++; // end weight
    }
    
    int countWordsEqualTo(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return 0;
            }
            node = node->children[ch];
        }
        return node->val;
    }

    int countWordsStartingWith(string prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) return 0;
            node = node->children[ch];
        }
        return node->w;
    }

    void erase(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            node->w--;
            node = node->children[ch];
        }
        node->w--;
        node->val--; 

        node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch]->w == 0) {
                delete node->children[ch];
                node->children[ch] = nullptr;
                break; 
            }
            node = node->children[ch];
        }
    }

};

