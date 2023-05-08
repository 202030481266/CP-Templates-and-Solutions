// https://leetcode.cn/problems/special-binary-string/



class Solution {
public:
    string makeLargestSpecial(string s) {
    	// 构造
    	int n = s.size();
    	if (n == 0) return "";
    	int stk = 0, pos = 0;
    	vector<string> ch;
    	for (int i = 0; i < n; ++i) {
    		if (s[i] == '1') {
    			if (stk++ == 0) pos = i;
    		}
    		else {
    			if (--stk == 0) {
    				ch.emplace_back("1" + makeLargestSpecial(s.substr(pos + 1, i - pos - 1)) + "0");
    			}
    		}
    	}
    	sort(ch.begin(), ch.end(), greater<string>());
    	string ans = accumulate(ch.begin(), ch.end(), ""s);
    	return ans;
    }
};