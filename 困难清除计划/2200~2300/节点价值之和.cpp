class Solution {
public:
    using ll = long long;
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();

        vector<int> g[n];
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<vector<ll>> dp(n, vector<ll>(2, 0));

        function<void(int, int)> dfs = [&](int u, int fa) {
            dp[u][0] += nums[u];
            dp[u][1] += nums[u] ^ k;
            ll loss = INT_MAX, cnt = 0, tot = 0;
            for (int& v : g[u]) {
                if (v != fa) {
                    dfs(v, u);
                    ll x = max(dp[v][0], dp[v][1]);
                    ll y = max(dp[v][0] + (nums[v] ^ k) - nums[v], dp[v][1] + nums[v] - (nums[v] ^ k));
                    if (y >= x) ++cnt;
                    loss = min(loss, abs(x - y));
                    tot += max(x, y);
                }
            }
            dp[u][cnt & 1] += tot;
            dp[u][(cnt & 1) ^ 1] += tot - loss;
        };

        dfs(0, 0);
        return max(dp[0][0], dp[0][1]);
    }
};