class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = s.size(), f[n + 1][26];
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < 26; ++j)
                f[i][j] = f[i - 1][j] + (s[i - 1] - 'a' == j);
        vector<bool> ans;
        for (auto& c : queries) {
            ++c[0]; ++c[1];
            int cnt = 0;
            for (int i = 0; i < 26; ++i) 
                if ((f[c[1]][i] - f[c[0] - 1][i]) & 1) ++cnt;
            ans.emplace_back(cnt / 2 <= c[2]);
        }
        return ans;
    }
};