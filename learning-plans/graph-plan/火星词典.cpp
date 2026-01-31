class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<int> g[26];
        vector<int> cnt(26), vis(26);
        int n = words.size(); 
        unordered_set<int> ord;
        for (string& s : words)
            for (char& ch : s) vis[ch - 'a'] = 1;
        for (int i = 0; i + 1 < n; ++i) {
            int m = min(words[i].size(), words[i + 1].size());
            int x = 0, y = 0;
            while (x < m && words[i][x] == words[i + 1][y]) ++x, ++y;
            if (x < m) {
                // (a -> b)
                ord.insert((words[i][x] - 'a') + 26 * (words[i + 1][y] - 'a'));
            }
            else if (words[i + 1].size() < words[i].size()) return "";
        }
        for (int c : ord) {
            int x = c % 26, y = c / 26;
            ++cnt[y];
            g[x].push_back(y);
        }
        string ans;
        queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] == 0 && vis[i]) {
                q.push(i);
                ans.push_back(char(i + 'a'));
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int& v : g[u]) {
                --cnt[v];
                if (cnt[v] == 0) {
                    q.push(v);
                    ans.push_back(char(v + 'a'));
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] > 0 && vis[i]) return "";
        }
        return ans;
    }
};