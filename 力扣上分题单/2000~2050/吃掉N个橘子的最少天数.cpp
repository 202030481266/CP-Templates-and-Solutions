// https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/
// 此题没有数学解法，很失望说实话
// 那就经典的记忆化搜索罢了，很简单


class Solution {
public:
	unordered_map<int, int> h;
    int minDays(int n) {
    	if (n <= 0) return 0;
    	if (h.count(n)) return h[n];
    	if (n == 1) return 1;
    	else if (n == 2 || n == 3) return 2;

    	int a = minDays(n / 3) + n % 3 + 1;
    	int b = minDays(n / 2) + n % 2 + 1;
    	h[n] = min(a, b);
    	return h[n];
    }
};