// https://leetcode.cn/problems/nth-magical-number/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int nthMagicalNumber(int n, int a, int b) {
    	const long long lab = lcm(a, b);

    	long long l = 0, r = min(1ll * n * a, 1ll * n * b);

    	while (l < r) {
    		long long mid = (l + r) / 2;
    		long long res = (mid / a) + (mid / b) - (mid / lab);
    		if (res < n) {
    			l = mid + 1;
    		}
    		else r = mid;
    	}
    	return l % mod;
    }
};