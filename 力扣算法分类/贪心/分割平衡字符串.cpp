// https://leetcode.cn/problems/split-a-string-in-balanced-strings/


class Solution {
public:
    int balancedStringSplit(string s) {
    	int cur = 0;
    	int ans = 0;
    	char ch;

    	for (auto c : s) {
    		if (cur == 0) {
    			cur = 1;
    			ch = c;
    		}
    		else {
    			if (c == ch) ++cur;
    			else --cur;
    		}
    		if (cur == 0) ++ans;
    	}
    	return ans;
    }
};