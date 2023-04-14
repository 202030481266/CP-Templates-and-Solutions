class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        int n = queries.size(), m = pattern.size();
        vector<bool> ans(queries.size(), false);
        for (int j = 0; j < n; ++j) {
            string s = queries[j];
            if (s.size() < m) continue; 
            int p = 0, flag = 1;
            for (int i = 0; i < s.size(); ++i) {
                if (p < m && s[i] == pattern[p]) ++p;
                else if (s[i] >= 'A' && s[i] <= 'Z') { flag = 0; break; }
            }
            ans[j] = (flag && p == m);
        }
        return ans;
    }
};