// https://leetcode.cn/problems/decoded-string-at-index/



class Solution {
public:
	string decodeAtIndex(string s, int k) {
""
		unsigned long long S = 0, T = 0;

		// 找到k字符所处的循环节
		int n = s.size(), pos = -1;

		for (int i = 0; i < n; ++i) {
			if (isalpha(s[i])) {
				++S;
			}
			else {
				// isdigit
				T = S;
				S = (S * (s[i] - '0'));
			}
			// check the length
			if (S >= k) {
				pos = i;
				break;
			}
		}
		string ans;

		if (isalpha(s[pos])) {
			// it also means S == k;
			ans.push_back(s[pos]);
			return ans;
		}

		// otherwise the kth character must appear in a cycle
		// and s[pos] must be a digit
		assert(isdigit(s[pos]));
		return decodeAtIndex(s.substr(0, pos), (k - 1) % T + 1);
	}
};