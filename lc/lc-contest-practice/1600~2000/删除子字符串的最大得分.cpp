// https://leetcode.cn/problems/maximum-score-from-removing-substrings/



class Solution {
public:
    int maximumGain(string ss, int x, int y) {
    	stack<char> s;
    	int ans = 0;
    	// find the max one
    	auto f = [&](string a, bool flag) {
	    	for (int i = 0; i < a.size(); ++i) {
	    		if (!s.empty()) {
	    			if (flag) {
	    				if (s.top() == 'a' && a[i] == 'b') {
	    					s.pop();
	    					ans += x;
	    				}
	    				else s.push(a[i]);
	    			}
	    			else {
	    				if (s.top() == 'b' && a[i] == 'a') {
	    					s.pop();
	    					ans += y;
	    				}
	    				else s.push(a[i]);
	    			}
	    		}
	    		else s.push(a[i]);
	    	}
	    };
	    bool target = (y > x ? false : true);
	    f(ss, target);
	    string temp;
	    while (!s.empty()) temp += s.top(), s.pop();
	    reverse(temp.begin(), temp.end());

        // cout << ans << ' ' << temp << endl;

	    f(temp, !target);
	    return ans;
    }
};