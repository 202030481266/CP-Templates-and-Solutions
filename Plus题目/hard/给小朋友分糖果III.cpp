class Solution {
public:
    using ll = long long;
    long long distributeCandies(int n, int limit) {
        if (limit * 3ll < n) {
            return 0;
        }
        
        // max(n - 2 * limit, 0) <= x <= min(n, limit)
        // max(0, N - limit) <= y <= min(n, limit), N = n - x
        // 数形结合

        auto f = [&](int N) -> ll {
            // [0, N]
            if (N < 0 || N > 2 * limit) return 0;
            if (N > limit) N = 2 * limit - N;
            return 1ll * (N + 2) * (N + 1) / 2; // [0, N]
        };

        if (limit <= n && n <= 2 * limit) {
            int left = n - limit, right = n;
            ll tot = f(limit) * 2 - limit - 1;
            return tot - f(left - 1) - f(right + 1);
        }
        else {
            if (n > limit) n -= limit;
            return f(n);
        }
    }
};