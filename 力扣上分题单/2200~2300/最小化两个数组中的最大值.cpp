// https://leetcode.cn/problems/minimize-the-maximum-of-two-arrays/
// 数学 + 容斥原理


class Solution {
	typedef long long ll;
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
    	ll lm = lcm(1ll * divisor1, 1ll * divisor2); // 注意要使用long long 不然会出错
    	auto check = [&](ll v) -> bool {
    		if (divisor1 == divisor2) {
    			// 相同的整除因子
    			return (uniqueCnt2 + uniqueCnt1 <= v - v / lm);
    		}
    		else if (lm == divisor1) {
    			int d1 = v / divisor1, d2 = v / divisor2, rem = v - d2;
    			// 第一个集合里面只能装载 整除d2但不能整除d1的+rem
    			// 第二个集合里面只能装载 rem
    			int x = uniqueCnt1 - (d2 - d1);
    			if (x < 0) x = 0;
    			return x + uniqueCnt2 <= rem;
    		}
    		else if (lm == divisor2) {
    			int d1 = v / divisor1, d2 = v / divisor2, rem = v - d1;
    			int x = uniqueCnt2 - (d1 - d2);
    			if (x < 0) x = 0;
    			return x + uniqueCnt1 <= rem;
    		}
    		else {
    			int d1 = v / divisor1, d2 = v / divisor2, d3 = v / lm, rem = v - d1 - d2 + d3;
    			int x = uniqueCnt1 - (d2 - d3), y = uniqueCnt2 - (d1 - d3);
    			if (x < 0) x = 0;
    			if (y < 0) y = 0;
    			return x + y <= rem;
    		}
    	};
    	ll l = 1, r = INT_MAX, ans = -1;
    	while (l <= r) {
    		ll mid = (l + r) >> 1;
    		if (check(mid)) ans = mid, r = mid - 1;
    		else l = mid + 1;
    	}
    	assert(ans != -1);
    	return ans;
    }
};