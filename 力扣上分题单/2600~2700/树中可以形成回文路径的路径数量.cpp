typedef pair<int, int> pii;
class Solution {
    vector<int> a;
    vector<vector<pii>> g;
public:
    void dfs(int u, int s) {
        a[u] = s;
        for (auto& [v, w] : g[u]) {
            dfs(v, s ^ (1 << w));
        }
    }
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        a.resize(n);
        g.resize(n);
        for (int i = 1; i < n; ++i) {
            g[parent[i]].emplace_back(i, s[i] - 'a');
        }
        dfs(0, 0);
        unordered_map<int, int> cnt;
        for (int i = 0; i < n; ++i) ++cnt[a[i]];
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            // no odd
            --cnt[a[i]];
            ans += cnt[a[i]];
            // one odd
            for (int j = 0; j < 26; ++j)
                ans += cnt[a[i] ^ (1 << j)];
        }
        return ans; 
    }
};