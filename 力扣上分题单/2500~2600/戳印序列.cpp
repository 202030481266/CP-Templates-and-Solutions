// 正难则反
class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int n = target.size(), m = stamp.size(), N = n - m + 1;
        vector<int> g[N];
        vector<int> du(N);
        vector<int> a[n];
        vector<int> vis(n);
        for (int i = 0; i + m - 1 < n; ++i) {
            for (int j = 0; j < m; ++j)
                if (target[j + i] != stamp[j]) {
                    ++du[i];
                    a[j + i].push_back(i);
                }
        }
        queue<int> q;
        vector<int> ans;
        for (int i = 0; i < N; ++i) {
            if (du[i] == 0) {
                q.emplace(i);
            }
        }
        int T = 10 * n;
        while (!q.empty() && T--) {
            int u = q.front();
            q.pop();
            ans.push_back(u);
            for (int i = u; i < u + m; ++i) {
                if (!vis[i]) {
                    vis[i] = true;
                    for (int& c : a[i]) {
                        --du[c];
                        if (du[c] == 0) 
                            q.emplace(c);
                    }
                }
            }
        }
        bool flag = true;
        for (int i = 0; i < N; ++i) if (du[i]) flag = false;
        if (flag && T >= 0) {
            reverse(ans.begin(), ans.end());
            return ans;
        }
        return {};
    }
};