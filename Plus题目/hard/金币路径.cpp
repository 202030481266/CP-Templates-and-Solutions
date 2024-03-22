// 从后往前动态规划的不幸在于字典序和路径权重的方向恰好相反，从后往前遍历就可以解决这个问题
// 最短路路径 a -> b， 那么必然存在最短路径 b -> a = a -> b
class Solution {
public:
    using pii = pair<int, int>;
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size();

        if (coins[0] == -1 || coins[n - 1] == -1)
            return {};

        vector<int> dis(n, INT_MAX / 2);
        vector<int> pre(n, -1);
        vector<bool> vis(n, false);

        queue<int> q;
        q.push(n - 1);
        dis[n - 1] = coins[n - 1];
        vis[n - 1] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = u - 1; i >= max(0, u - maxJump); --i) {
                if (coins[i] != -1) {
                    if (dis[i] > dis[u] + coins[i]) {
                        dis[i] = dis[u] + coins[i];
                        pre[i] = u;
                        if (!vis[i]) {
                            vis[i] = 1;
                            q.push(i);
                        }
                    }
                    else if (dis[i] == dis[u] + coins[i] && pre[i] > u) {
                        pre[i] = u;
                    }
                }
            }
        }
        vector<int> ans;
        int cur = 0;
        while (cur != -1) {
            ans.push_back(cur + 1);
            cur = pre[cur];
        }
        if (ans.back() != n) return {};
        return ans;
    }
};