class Solution {
public:
    using ll = long long;
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        // dijkstra 算法
        int n = regular.size(); 
        ll dp[n + 1][2];
        memset(dp, 0x3f, sizeof(dp));

        dp[0][0] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
        q.emplace(0, 0);
        while (!q.empty()) {
            ll d = q.top().first;
            int x = q.top().second / 2, y = q.top().second % 2;
            q.pop();
            if (d != dp[x][y]) continue;
            if (y == 0) {
                if (dp[x][1] > d + expressCost) {
                    dp[x][1] = d + expressCost;
                    q.emplace(dp[x][1], x * 2 + 1);
                }
                if (x + 1 <= n && dp[x + 1][0] > d + regular[x]) {
                    dp[x + 1][0] = d + regular[x];
                    q.emplace(dp[x + 1][0], (x + 1) * 2);
                } // x -> x + 1
            }
            else {
                if (dp[x][0] > d) {
                    dp[x][0] = d;
                    q.emplace(dp[x][0], x * 2);
                }
                if (x + 1 <= n && dp[x + 1][1] > d + express[x]) {
                    dp[x + 1][1] = d + express[x];
                    q.emplace(dp[x + 1][1], (x + 1) * 2 + 1);
                }
            }
        }
        vector<ll> ans(n);
        for (int i = 1; i <= n; ++i)
            ans[i - 1] = min(dp[i][0], dp[i][1]);
        return ans;
    }
};