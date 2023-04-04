class Solution {
public:
    map<long long, int> factorize(long long n) {
        map<long long, int> factors;
        for (int d = 2; (long long)d * d <= n; d++) {
            while (n % d == 0) {
                ++factors[d];
                n /= d;
            }
        }
        if (n > 1) {
            ++factors[n];
        }
        return factors;
    }
    int commonFactors(int a, int b) {
        int tmp = gcd(a, b);
        auto factors = factorize(tmp);
        int ans = 1;
        for (auto [key, value] : factors) ans *= (1 + value);
        return ans;
    }
};