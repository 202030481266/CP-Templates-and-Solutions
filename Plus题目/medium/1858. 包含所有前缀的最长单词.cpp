#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int Maxn = 100010;

struct Trie {
    int ch[Maxn][26], val[Maxn], sz;

    int ans;
    vector<char> cur;
    vector<char> res;
    
    void init() {
        sz = 0;
        ans = 0;
        cur.clear();
        res.clear();
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
        }
        val[u]++;
    }

    void dfs(int u, int dep) {
        if (dep > ans) {
            ans = dep;
            res = cur;
        }
        for (int i = 0; i < 26; ++i) {
            if (ch[u][i] && val[ch[u][i]] > 0) {
                cur.push_back((char)('a' + i));
                dfs(ch[u][i], dep+1);
                cur.pop_back();
            }
        }
    }
    
    void query(string s) {
        int u = 0, len = s.size();
        for (int i = 0; i < len; i++) {
            int v = s[i] - 'a';
            u = ch[u][v];
            if (val[u] == 0) break;
        }
    }
} t;

class Solution {
public:
    string longestWord(vector<string>& words) {
        int n = words.size();
        t.init();
        for (string s : words) t.insert(s);
        t.dfs(0, 0);
        return string(t.res.begin(), t.res.end());
    }
};