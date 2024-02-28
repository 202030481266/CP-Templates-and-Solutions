class Solution {
public:
    void dfs(string& s, int p, string& cur, vector<string>& ans) {
        if (p == s.size()) {
            ans.push_back(cur);
            return;
        }
        if (s[p] == '{') {
            int i = p;
            while (s[i] != '}') ++i;
            for (int j = p + 1; j < i; ++j) {
                if (s[j] != ',') {
                    cur.push_back(s[j]);
                    dfs(s, i + 1, cur, ans);
                    cur.pop_back();
                }
            }
        }
        else {
            cur.push_back(s[p]);
            dfs(s, p + 1, cur, ans);
            cur.pop_back();
        }
    }
    vector<string> expand(string s) {
        vector<string> res;
        string cur = "";
        dfs(s, 0, cur, res);
        sort(res.begin(), res.end());
        return res;
    }
};