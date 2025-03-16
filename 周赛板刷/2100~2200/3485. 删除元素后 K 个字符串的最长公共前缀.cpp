#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size(), N = 0, tot = 0;
        for (string& s : words) N += (int)s.size();
        vector ch(N + 1, vector<int>(26, 0)); 
        vector<int> val(N + 1, 0), mx(N + 1, 0);
        // Trie
        auto insertTrie = [&](auto&& dfs, string& s, int p, int r) -> void {
            if (p == (int)s.size()) return;
            int c = s[p] - 'a';
            if (!ch[r][c]) ch[r][c] = ++tot;
            r = ch[r][c];
            val[r]++;
            dfs(dfs, s, p + 1, r);
            mx[r] = (val[r] >= k) ? p + 1 : 0;
            for (int i = 0; i < 26; ++i) {
                mx[r] = max(mx[r], mx[ch[r][i]]);
            }
        };
        auto delTrie = [&](auto&& dfs, string& s, int p, int r) -> void {
            if (p == (int)s.size()) return;
            int c = s[p] - 'a';
            r = ch[r][c];
            val[r]--;
            dfs(dfs, s, p + 1, r);
            mx[r] = (val[r] >= k) ? p + 1 : 0;
            for (int i = 0; i < 26; ++i) {
                mx[r] = max(mx[r], mx[ch[r][i]]);
            }
        };
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) insertTrie(insertTrie, words[i], 0, 0);
        for (int i = 0; i < n; ++i) {
            delTrie(delTrie, words[i], 0, 0);
            for (int j = 0; j < 26; ++j) {
                ans[i] = max(ans[i], mx[ch[0][j]]);
            }
            insertTrie(insertTrie, words[i], 0, 0);
        }
        return ans;
    }
};