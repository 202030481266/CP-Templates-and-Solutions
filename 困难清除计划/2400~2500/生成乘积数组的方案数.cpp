typedef long long ll;
class Solution {
    static constexpr int mod = 1e9 + 7;
    static constexpr int N = 10010;
    ll fac[N], ifac[N];
    vector<int> factors[N];
    int dp[20][N], mx[N];
public:
    ll mul(ll a, ll b) {
        ll ans = 1;
        for (; b; b >>= 1) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
        }
        return ans;
    }
    ll inv(ll x) {
        return mul(x, mod - 2) % mod;
    }
    ll binomial(int x, int y) {
        return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
    }
    void solve() {
        fac[0] = 1ll;
        for (int i = 1; i <= 10000; ++i) fac[i] = fac[i - 1] * i % mod;
        ifac[10000] = inv(fac[10000]);
        for (int i = 10000 - 1; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % mod;
        for (int i = 2; i <= 10000; ++i)
            for (int j = i; j <= 10000; j += i)
                factors[j].push_back(i);
        dp[0][1] = 1;
        for (int i = 2; i <= 10000; ++i) {
            mx[i] = (int)(log2(i));
            for (int j = 1; j <= mx[i]; ++j)
                for (int& x : factors[i])
                    dp[j][i] = (dp[j][i] + dp[j - 1][i / x]) % mod;
        }
    }
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        solve();
        vector<int> ans;
        for (auto& q : queries) {
            ll res = 0;
            for (int i = 1; i <= min(mx[q[1]], q[0]); ++i) {
                res = (res + binomial(q[0], i) * dp[i][q[1]]) % mod;
            }
            if (res == 0) ++res;
            ans.push_back(res);
        }
        return ans;
    }
};
