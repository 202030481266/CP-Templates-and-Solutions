// https://leetcode.cn/problems/longest-chunked-palindrome-decomposition/



class Solution {
public:
	bool check(string s, int len) {
		// check the prefix and sufix of len is ok
		int l = 0, r = s.size() - len;
		while (r < s.size() && s[l] == s[r]) ++l, ++r;
		return r >= s.size();
	}
    int longestDecomposition(string text) {
    	int n = text.size();

    	if (n <= 1) return n; 

    	int temp = 0;
    	for (int len = 1; len <= n / 2; ++len) {
    		if (check(text, len)) {
    			temp = len;
    			break;
    		}
    	}
    	if (temp == 0) return 1;
    	return 2 + longestDecomposition(text.substr(temp, n - 2 * temp));
    }
};