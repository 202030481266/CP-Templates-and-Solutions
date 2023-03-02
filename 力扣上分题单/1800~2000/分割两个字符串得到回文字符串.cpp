// https://leetcode.cn/problems/split-two-strings-to-make-palindrome/



class Solution {
public:
    bool checkPalindromeFormation(string aa, string bb) {
    	int n = aa.size();

    	auto f = [&](string s) {
    		int l = 0, r = s.size() - 1;
    		while (l < r) {
    			if (s[l] != s[r]) return false;
    			++l, --r;
    		}
    		return true;
    	};

    	auto g = [&](string a, string b) {
	    	int l = 0, r = n - 1;
	    	while (l < r && a[l] == b[r]) ++l, --r;
	    	// stop match
	    	if (l >= r) return true;
	    	string x = a.substr(l, r - l + 1);
	    	string y = b.substr(l, r - l + 1);
	    	return (f(x) || f(y));
	    };

	    return g(aa, bb) || g(bb, aa);
    }
};