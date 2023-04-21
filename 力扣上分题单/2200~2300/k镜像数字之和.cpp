// https://leetcode.cn/problems/sum-of-k-mirror-numbers/



class Solution {
public:
	// 将x进制数字s转换成一个y进制 （进制k满足2<=k<=36）
	string transform(int x, int y, string s) {
		string res;
		int sum = 0;
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '-') continue;
			if (isdigit(s[i])) sum = sum * x + s[i] - '0';
			else sum = sum * x + s[i] - 'A' + 10;
		}
		while (sum) {
			char tmp = sum % y;
			sum /= y;
			if (tmp <= 9) tmp += '0';
			else tmp = tmp - 10 + 'A';
			res = tmp + res;
		}
		if (res.length() == 0) res = "0";
		if (s[0] == '-') res = '-' + res;
		return res;
	}
    long long kMirror(int k, int n) {
        
    }
};