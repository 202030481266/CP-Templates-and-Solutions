// https://leetcode.cn/problems/minimum-non-zero-product-of-the-array-elements/



class Solution {
public:
	static constexpr int mod = 1000000007;
	long long pow_mod(long long x, long long n) {
	    long long res = 1;
	    for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
	        if ((n & 1) != 0)
	            res = (long long)(res * p % mod);
	    return res;
	}
    int minNonZeroProduct(int p) {
    	long long a = (1ll << p) - 2;
    	long long b = (1ll << (p - 1)) - 1;
    	return pow_mod(a % mod, b) * ((a + 1) % mod) % mod;
    }
};