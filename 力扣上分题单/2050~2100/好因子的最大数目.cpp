// https://leetcode.cn/problems/maximize-number-of-nice-divisors/



class Solution {
public:
	static constexpr int mod = 1000000007;
	int pow_mod(int x, int n) {
	    int res = 1;
	    for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
	        if ((n & 1) != 0)
	            res = (int)(res * p % mod);
	    return res;
	}
    int maxNiceDivisors(int primeFactors) {
    	// 特判
        if (primeFactors == 1) return 1;
    	int k = primeFactors % 3, m;
    	if (k == 1 || k == 0) m = primeFactors / 3;
    	else m = primeFactors / 3 + 1;

    	k = primeFactors % m;
    	int tmp = (primeFactors - k) / m;

    	return pow_mod(tmp, m - k) * 1ll * pow_mod(tmp + 1, k) % mod;
    }
};