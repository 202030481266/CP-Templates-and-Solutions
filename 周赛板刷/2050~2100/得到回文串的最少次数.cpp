// https://leetcode.cn/problems/minimum-number-of-moves-to-make-palindrome/
// 贪心好题，非常牛逼
// 给定一个字符串 
// 已知S，求出将其变为回文串所需要的最小邻位交换次数。
// 结论： 每次交换最外边出现的字母不劣 (可以假设证明交换所需要的次数)



class Solution {
public:
    int minMovesToMakePalindrome(string s) {
    	if (s.size() == 0) return 0;
    	int cnt = 0, n = s.size();
    	string tmp;
    	for (int i = n - 1; i >= 0; --i) {
    		if (s[i] == s[0] && i != 0) {
    			for (int j = 1; j < i; ++j) tmp += s[j];
    			for (int j = i + 1; j < n; ++j) tmp += s[j];
    			cnt += (n - i - 1);
    			break;
    		}
    		if (i == 0) {
    			cnt += (n / 2);
    			tmp = s.substr(1);
    		}
    	}
    	return cnt + minMovesToMakePalindrome(tmp);
    }
};

