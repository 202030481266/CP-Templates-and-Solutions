// https://leetcode.cn/problems/check-if-a-parentheses-string-can-be-valid/
// 有效括号字符串的变种题目


class Solution {
public:
    bool canBeValid(string s, string locked) {
        int a = 0, b = 0, n = s.size();

        if (n & 1) return false;  // 长度为奇数不可能匹配成功

        for (int i = 0; i < n; ++i) {
            if (locked[i] == '0') {
                b = max(b - 1, 0);
                ++a;
            }
            else if (s[i] == '(') {
                ++b;
                ++a;
            }
            else {
                b = max(b - 1, 0);
                --a;
                if (a < 0) return false;
            }
        }
        return b == 0;
    }
};