class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int ans = 0;
        for (long long i = 1; (i + 1) * i <= 2ll * n; ++i) {
            if (2ll * n % i == 0) {
                long long x = 2ll * n / i + 1 - i;
                if (x % 2 == 0) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};