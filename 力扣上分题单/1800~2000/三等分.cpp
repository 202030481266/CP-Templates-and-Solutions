// https://leetcode.cn/problems/three-equal-parts/
// 模拟，如果一的个数不是三的倍数就肯定不行，然后把一三等分即可


class Solution {
public:
	vector<int> threeEqualParts(vector<int>& arr) {
		int n = arr.size();
		bool allzero = true;
		for (int i = 0; i < n; ++i)
			if (arr[i]) {
				allzero = false;
				break;
			}
		if (allzero) return { 0,2 };

		vector<int> onePos;
		for (int i = 0; i < n; ++i)
			if (arr[i]) onePos.emplace_back(i);

		int m = onePos.size();
		if (m % 3) return { -1, -1 }; // 特判

		int t = m / 3;
		int len = (n - onePos[2 * t]); // highbit of length
		
		int a = onePos[0], b = onePos[t], c = onePos[2 * t]; // the begin of three strings

		if (a + len - 1 >= b || b + len - 1 >= c) return { -1,-1 };

		for (int i = 2; i <= len; ++i) {
			if (arr[a + i - 1] != arr[b + i - 1] || arr[a + i - 1] != arr[c + i - 1])
				return { -1,-1 };
		}
		return { a + len - 1, b + len };
	}
};