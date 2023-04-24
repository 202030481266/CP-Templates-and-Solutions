// https://leetcode.cn/problems/check-if-point-is-reachable/



class Solution {
public:
    bool isReachable(int X, int Y) {
    	while (X % 2 == 0) X /= 2;
    	while (Y % 2 == 0) Y /= 2;
    	return gcd(X, Y) == 1;
    }
};