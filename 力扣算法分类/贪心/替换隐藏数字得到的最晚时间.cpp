// https://leetcode.cn/problems/latest-time-by-replacing-hidden-digits/



class Solution {
public:
    string maximumTime(string time) {
    	string ans = time;
    	for (int i = 0; i < 5; ++i) {
    		if (time[i] == '?') {
    			if (i == 0) {
    				if (time[1] != '?' && time[1] - '0' > 3) ans[0] = '1';
    				else ans[0] = '2';
    			}
    			else if (i == 3) ans[i] = '5';
    			else if (i == 4) ans[i] = '9';
    			else if (i == 1) {
    				if (ans[0] == '2') ans[i] = '3';
    				else ans[i] = '9';
    			}
    		}
    	}
    	return ans;
    }
};