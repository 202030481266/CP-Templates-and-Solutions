class Solution {
    typedef pair<int, int> pii;
    int cnt[100010], tot = 0;
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int m = queries.size();
        vector<pii> q;
        vector<int> ans(m); 
        for(int i = 0; i < m; ++i) q.emplace_back(queries[i] - x, i);
        sort(q.begin(), q.end());
        sort(logs.begin(), logs.end(), [&](auto& x, auto& y){
            return x[1] < y[1];
        });
        int l = 0, r = 0;
        for (int i = 0; i < m; ++i) {
            int L = q[i].first, R = L + x;
            while (r < logs.size() && logs[r][1] <= R) {
                ++cnt[logs[r][0]];
                if (cnt[logs[r][0]] == 1) ++tot;
                ++r;
            }
            while (l < r && logs[l][1] < L) {
                --cnt[logs[l][0]];
                if (cnt[logs[l][0]] == 0) --tot;
                ++l;
            }
            ans[q[i].second] = n - tot;
        }
        return ans;
    }
};