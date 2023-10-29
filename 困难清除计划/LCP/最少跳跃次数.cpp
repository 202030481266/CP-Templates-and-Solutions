class Solution {
public:
    int minJump(vector<int>& jump) {
        int n = jump.size(), dp[n];
        memset(dp, -1, sizeof(dp));

        dp[0] = 0;
        int mx = -1;  // the rightmost point
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u + jump[u] > n - 1) return dp[u] + 1;

            // jump to right
            if (dp[u + jump[u]] == -1) {
                dp[u + jump[u]] = dp[u] + 1;
                q.push(u + jump[u]);
            }

            // jump to left
            if (u > mx) {
                for (int i = mx + 1; i < u; ++i) {
                    if (dp[i] == -1) {
                        dp[i] = dp[u] + 1;
                        q.push(i);
                    }
                }
                mx = u;
            }
        }

        return -1;

    }
};