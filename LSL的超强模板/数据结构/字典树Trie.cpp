// Trie
// 个人觉得最好用的写法
#include <bits/stdc++.h>
using namespace std;

const int Maxn = 100;

struct Trie {
    int ch[Maxn][26], val[Maxn], sz;
    
    void init() {
        sz = 0;
        memset(val, 0, sizeof(val));
        memset(ch[0], 0, sizeof(ch[0]));
    }
    
    void insert(string s) {
        int u = 0, len = s.size();
        for (int i = 0; i < len; i++) {
            int v = s[i] - 'a';
            if (!ch[u][v]) {
                ch[u][v] = ++sz;
                memset(ch[sz], 0, sizeof(ch[sz]));
            }
            u = ch[u][v];
            val[u]++;
        }
    }
    
    void query(string s) {
        int u = 0, len = s.size();
        for (int i = 0; i < len; i++) {
            int v = s[i] - 'a';
            u = ch[u][v];
            // Uncomment the line below to see the output
            // cout << s[i] << " " << val[u] << endl;
            if (val[u] == 0) break;
        }
    }
};

int main() {
    array<string, 3> ss;
    Trie tree;
    tree.init();
    
    for (auto &s : ss) cin >> s;
    for (auto &s : ss) tree.insert(s);
    for (auto &s : ss) {
        tree.query(s);
        putchar('\n');
    }

    return 0;
}
