class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size();
        vector<int> g[401];
        for (int i = 0; i < n; ++i)
            g[(int)words[i].size()].push_back(i);
        vector<string> ans;
        for (int i = 0; i < n; ++i) {
            string& s = words[i];
            int m = s.size(), mx = 0;
            for (int& id : g[m]) {
                if (words[id][m - 1] == s[m - 1] && id != i) {
                    int p = 0;
                    while (p < m && s[p] == words[id][p])
                        ++p;
                    mx = max(mx, p);
                }
            }
            // cout << s << ' '<< mx << endl;
            if (mx >= m - 3) ans.push_back(s);
            else ans.push_back(s.substr(0, mx + 1) + to_string(m - mx - 2) + s.substr(m - 1, 1));
        }
        return ans;
    }
};