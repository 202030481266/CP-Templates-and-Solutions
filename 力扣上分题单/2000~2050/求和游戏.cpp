// https://leetcode.cn/problems/sum-game/description/



class Solution {
public:
	bool sumGame(string num) {
		int n = num.size();
		int x = 0, y = 0, l = 0, r = 0;

		for (int i = 0; i < n / 2; ++i) {
			if (isdigit(num[i]))
				x += (num[i] - '0');
			else ++l;
		}
		for (int i = n / 2; i < n; ++i) {
			if (isdigit(num[i]))
				y += (num[i] - '0');
			else ++r;
		}

		// odd times of '?' must win
		if ((l + r) & 1) return true;
		
		int t = abs(r - l), sub = abs(x - y);

		// can judge immediately
		if (l == r) return (x == y) ? false : true;
		if ((x > y && l > r) || (y > x && r > l)) return true;

		if (sub < (t / 2) * 9) return true;
		if ((sub - 9) > (t / 2 - 1) * 9) return true;
		return false;
	}
};