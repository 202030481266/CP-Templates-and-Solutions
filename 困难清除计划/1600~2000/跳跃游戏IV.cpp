class Solution {
    unordered_map<int, vector<int>> pos;
    unordered_map<int, bool> vis;
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size(), dp[n];
        memset(dp, -1, sizeof(dp));

        // 分桶
        for (int i = 0; i < n; ++i)
            pos[arr[i]].push_back(i);

        // bfs
        queue<int> q;
        dp[0] = 0;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n - 1) break;
            if (!vis[arr[u]]) {
                // 只会扩展一次并且一次性全部计算
                for (int& p : pos[arr[u]]) {
                    if (p == u || dp[p] != -1) continue;
                    dp[p] = dp[u] + 1;
                    q.push(p);
                }
                vis[arr[u]] = 1;
            }
            if (u - 1 >= 0 && dp[u - 1] == -1) {
                dp[u - 1] = dp[u] + 1;
                q.push(u - 1);
            }  
            if (u + 1 < n && dp[u + 1] == -1) {
                dp[u + 1] = dp[u] + 1;
                q.push(u + 1);
            }
        }
        return dp[n - 1];
    }
};