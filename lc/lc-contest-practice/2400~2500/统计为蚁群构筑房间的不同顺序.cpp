typedef unsigned long long ll;
class Solution {
    static constexpr int mod = 1e9 + 7;
    ll dp[100010], fac[100010], ifac[100010];
    int n, siz[100010];
    vector<vector<int>> g;
public:
    ll mul(ll a, ll b) {
        ll ans = 1ll;
        for (; b; b >>= 1) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
        }
        return ans;
    }
    ll inv(ll x) {
        return mul(x, mod - 2);
    }
    ll binomial(int x, int y) {
        return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
    }
    void dfs(int u) {
        dp[u] = 1;
        for (int v : g[u]) {
            dfs(v);
            siz[u] += siz[v];
            dp[u] = (dp[u] * dp[v]) % mod;
        }
        int tmp = 0;
        for (int v : g[u]) {
            dp[u] = dp[u] * binomial(siz[u] - tmp, siz[v]) % mod;
            tmp += siz[v];
        }
        siz[u] += 1;
    }
    int waysToBuildRooms(vector<int>& prev) {
        n = prev.size();
        g = vector(n, vector<int>());
        for (int i = 1; i < n; ++i)
            g[prev[i]].push_back(i);
        fac[0] = 1ll;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
        ifac[n] = inv(fac[n]);
        for (int i = n - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
        dfs(0);
        return dp[0];
    }
};
