class Solution {
    using ll = long long;
public:
    int maxNumberOfAlloys(int n, int k, int b, vector<vector<int>>& c, vector<int>& stock, vector<int>& cost) {
        vector<ll> sum(n + 1);

        auto check = [&](int x, int v) -> bool {
            ll u = 0;
            for (int i = 0; i < n; ++i) {
                if (1ll * stock[i] >= 1ll * v * c[x][i]) continue;
                u += (1ll * v * c[x][i] - stock[i]) * cost[i];
            }
            return u <= 1ll * b;
        };


        auto f = [&](int x) -> int {
            ll s = 0;
            int l = 0, r = 0;
            for (int i = 0; i < n; ++i)
                s += 1ll * c[x][i] * cost[i];
            for (int i = 0; i < n; ++i)
                r = max(r, stock[i] / c[x][i]);
            r += r + b / s + 2;
            while (l + 1 < r) {  // [l, r)
                int mid = (l + r) >> 1;
                if (check(x, mid)) l = mid;
                else r = mid;
            }
            return l;
        };

        int ans = 0;
        for (int i = 0; i < k; ++i) {
            ans = max(ans, f(i));
        }
        return ans;
    }
};