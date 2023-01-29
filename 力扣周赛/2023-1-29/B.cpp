class Solution {
public:
    static constexpr int mod = 1000000007;
    int pow_mod(int x, int n, int mod) {
        int res = 1;
        for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
            if ((n & 1) != 0)
                res = (int)(res * p % mod);
        return res;
    }
    int monkeyMove(int n) {
        return (pow_mod(2, n, mod) - 2 + mod) % mod;
    }
};