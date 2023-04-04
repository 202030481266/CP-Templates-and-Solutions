// https://leetcode.cn/problems/preimage-size-of-factorial-zeroes-function/



class Solution {
public:
    int preimageSizeFZF(int k) {

    	auto f = [&](long long v) {
    		// 取决于5的个数，因为每两个数有一个2，每五个数才一个5
    		long long res = 0;
    		for (long long i = 5; v / i; i *= 5) {
    			res += (v / i);
    		}
    		return res;
    	};

    	long long l = 0, r = 2000000000000;
    	while (l <= r) {
    		long long mid = (l + r) >> 1;
    		long long res = f(mid);
    		if (res == 1ll * k) {
    			return 5;
    		}
    		else if (res > k) r = mid - 1;
    		else l = mid + 1;
    	}
		return 0;
    }
};