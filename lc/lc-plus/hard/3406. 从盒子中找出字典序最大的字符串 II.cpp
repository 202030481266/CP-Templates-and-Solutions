#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// SAM 是最为快速的解法
const int maxn = 2e5 + 7;
struct SAM {
    int len[maxn<<1], link[maxn<<1], ch[maxn<<1][26], f[maxn<<1][26];
    int siz, last;
    
    void init(int n) {
        // 阴间的lc会因为过度的初始化超时
        memset(len, 0, sizeof(int) * (n << 1));
        memset(link, 0, sizeof(int) * (n << 1));
        memset(ch, 0, sizeof(int) * (n << 1) * 26);
        memset(f, 0, sizeof(int) * (n << 1) * 26);
        siz = last = 0;
        link[0] = -1;
    }

    void extend(string s) {
        int n = s.size();
        for (int pos = 0; pos < n; ++pos) {
            int cur = ++siz, p = last, c = s[pos] - 'a';
            len[cur] = len[p] + 1;
            while (p != -1 && !ch[p][c]) {
                ch[p][c] = cur;
                p = link[p];
            }
            if (p == -1) link[cur] = 0;
            else {
                int q = ch[p][c];
                if (len[q] == len[p] + 1) link[cur] = q;
                else {
                    int copy = ++siz;
                    len[copy] = len[p] + 1;
                    link[copy] = link[q];
                    for (int i = 0; i < 26; ++i) {
                        ch[copy][i] = ch[q][i];
                    }
                    while (p != -1 && ch[p][c] == q) {
                        ch[p][c] = copy;
                        p = link[p];
                    }
                    link[q] = link[cur] = copy;
                }
            }
            last = cur;
        }
    }

    string get(int k) {
        // 找到长度不大于k的字典序最大子串
        string res;
        int cur = 0;
        while (k) {
            int flag = 0;
            for (int i = 25; i >= 0; --i) {
                if (ch[cur][i]) {
                    flag = 1;
                    cur = ch[cur][i];
                    res.push_back(i + 'a');
                    break;
                }
            }
            if (!flag) break;
            --k;
        }
        return res;
    }
} sam;

class Solution {
public:
    string answerString(string word, int numFriends) {
        if (numFriends == 1) return word;
        sam.init(word.size());
        sam.extend(word);
        return sam.get(word.size()-numFriends+1);
    }
};