// https://leetcode.cn/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/



class Solution {
public:
	int minFlips(string s) {
		int n = s.size();
		if (n == 1) return 0;

		// 滑动窗口统计问题
		// 首先需要拼接
		s = s + s;
		int ans = INT_MAX;
		int x = 0, y = 0;
		// x is 01010101
		// y is 10101010
		for (int i = 0; i < n; ++i) {
			if (i & 1) {
				if (s[i] == '0') ++x;
				else ++y;
			}
			else {
				if (s[i] == '1') ++x;
				else ++y;
			}
		}
		for (int i = n; i < 2 * n; ++i) {
			// transform intoo 0 1 0 1....
			ans = min(ans, min(x, y));
			int nx = y, ny = x;
			if (s[i - n] == '1') {
				--ny;
			}
			else --nx;
			if (n & 1) {
				// means 01010 ends with 0, 10101 ends with 1
				if (s[i] != '0') ++nx;
				else ++ny;
			}
			else {
				if (s[i] != '1') ++nx;
				else ++ny;
			}
			x = nx;
			y = ny;
		}
		ans = min(ans, min(x, y));
		return ans;
	}
};