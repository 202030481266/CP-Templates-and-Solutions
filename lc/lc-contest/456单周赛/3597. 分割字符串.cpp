class Solution {
public:
    vector<string> partitionString(string s) {
        unordered_map<int, array<int, 26>> trie;
        vector<string> ans;
        int n = s.size(), cur = 0, l = 0, tot = 0;
        for (int i = 0; i < n; ++i) {
            if (!trie[cur][s[i] - 'a']) {
                ans.push_back(s.substr(l, i - l + 1));
                trie[cur][s[i] - 'a'] = ++tot;
                cur = 0;
                l = i + 1;
            }
            else {
                cur = trie[cur][s[i] - 'a'];
            }
        }
        return ans;
    }
};