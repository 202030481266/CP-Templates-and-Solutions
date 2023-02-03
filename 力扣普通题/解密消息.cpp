class Solution {
public:
    string decodeMessage(string key, string message) {
        vector<char> a;
        vector<char> b(26);
        vector<bool> vis(26);

        for (auto c : key)
            if (islower(c) && !vis[c - 'a']) a.emplace_back(c), vis[c - 'a'] = true;
        for (int i = 0; i < 26; ++i)
            b[c - 'a'] = ('a' + i);
        for (auto &c : message)
            if (islower(c)) c = b[c - 'a'];
        return message;
    }
};