class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int countOrders(int n) {
        unsigned long long ans = 1;
        for (int i = 2; i <= n; ++i)
            ans = (i * (2 * i - 1) % mod) * ans % mod;
        return ans;
    }
};