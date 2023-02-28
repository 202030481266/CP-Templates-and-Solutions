// https://leetcode.cn/problems/longest-happy-string/
// 贪心+模拟，击败100%


class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
    	string ans;

    	if (a >= b) {
    		if (a >= c) ans += 'a', --a;
    		// c > a
    		else ans += 'c', --c;
    	}
    	// b > a
    	else {
    		if (b >= c) ans += 'b', --b;
    		// c > b
    		else ans += 'c', --c;
    	}

    	bool flag = false;
    	while (true) {
    		char ch = ans.back();
    		if (ch == 'a') {
    			// means there 2 'a' before
    			if (flag) {
    				if (b == 0 && c == 0) break;
    				else if (b > c) ans += 'b', --b;
    				else ans += 'c', --c;
    				flag = false;
    			}
    			else {
    				if (a == 0 && b == 0 && c == 0) break;
    				else if (a >= b && a >= c) {
    					// we should use the 'a' as greedy
    					ans += 'a', --a;
    					flag = true;
    				}
    				else {
    					if (b > c) ans += 'b', --b;
    					else ans += 'c', --c;
    					flag = false;
    				}
    			}
    		}
    		else if (ch == 'b') {
    			// means there 2 'b' before
    			if (flag) {
    				if (a == 0 && c == 0) break;
    				else if (a > c) ans += 'a', --a;
    				else ans += 'c', --c;
    				flag = false;
    			}
    			else {
    				if (a == 0 && b == 0 && c == 0) break;
    				else if (b >= a && b >= c) {
    					ans += 'b', --b;
    					flag = true;
    				}
    				else {
    					if (a > c) ans += 'a', --a;
    					else ans += 'c', --c;
    					flag = false;
    				}
    			}
    		}
    		else {
    			// means there 2 'c' before
    			if (flag) {
    				if (b == 0 && a == 0) break;
    				else if (a > b) ans += 'a', --a;
    				else ans += 'b', --b;
    				flag = false;
    			}
    			else {
    				if (a == 0 && b == 0 && c == 0) break;
    				else if (c >= a && c >= b) {
    					ans += 'c', --c;
    					flag = true;
    				}
    				else {
    					if (a > b) ans += 'a', --a;
    					else ans += 'b', --b;
    					flag = false;
    				}
    			}
    		}
    	}
    	return ans;
    }
};