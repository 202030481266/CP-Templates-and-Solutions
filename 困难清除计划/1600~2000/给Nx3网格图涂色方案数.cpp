class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int numOfWays(int n) {
        long long a = 1, b = 1;
        for (int i = 0; i < n; ++i) {
            long long aa = 2 * (a + b) % mod, bb = (3 * b + 2 * a) % mod;
            a = aa, b = bb;
        }
        return 6 * (a + b) % mod;
    }
};