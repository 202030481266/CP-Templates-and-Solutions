class Solution {
    using ll = long long;
public:
    long long findMaximumNumber(long long k, int x) {
        // 数位dp似乎只有这一个比较好的方法，否则非常难二分
        ll dp[64];
        ll l = 0, r, sum = 0, pos;
        dp[0] = 0;
        for (int i = 1; ; ++i) {
            dp[i] = 2 * dp[i - 1];
            if (i % x == 0) dp[i] += (1ll << (i - 1)); // 0 or 1
            if (dp[i] > k) {
                r = (1ll << i) - 1;
                l = (r >> 1);
                pos = i;
                break;
            }
        }
        // [1, pos)
        cout << r << endl;

        ll f[64][64];

        function<ll(int,bool,int, ll&)> dfs = [&](int p, bool is_limit, int cnt, ll& cur) -> ll {
            if (p == 0) return cnt;
            if (!is_limit && f[p][cnt] != -1) return f[p][cnt];
            ll rs = 0;
            int up = is_limit ? ((cur >> (p - 1)) & 1) : 1;
            for (int i = 0; i <= up; ++i) {
                bool c = (i > 0) && (p % x == 0);
                rs += dfs(p - 1, is_limit && i == up, (c ? cnt + 1 : cnt), cur);
            }
            if (!is_limit) f[p][cnt] = rs;
            return rs;
        };

        auto check = [&](ll r) -> bool {
            memset(f, -1, sizeof(f));
            ll res = dfs(pos, true, 0, r);
            return res <= k;
        };

        ll ans = 0;

        while (l <= r) {
            ll mid = (l + r) >> 1; 
            if (check(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }

        return ans;

    }
};
