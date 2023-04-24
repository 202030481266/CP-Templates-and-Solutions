class Solution {
public:
    string lastSubstring(string s) {
        // 字符串算法都是来源于暴力，然后从中找到比较优秀的结构，设计算法
        // 答案一定是后缀子串，并且可以尝试暴力匹配
        int n = s.size(), i = 0, j = 1, k = 0;
        while (i < n && j < n) {
            k = 0;
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
            if (s[i + k] == s[j + k]) return s.substr(i, n - i);
            if (s[i + k] > s[j + k]) 
                j = j + k + 1;
            else {
                if (i + k + 1 >= j) {
                    i = i + k + 1;
                    j = i + 1;
                }
                else i = i + k + 1;
            }
        }
        return s.substr(i, n - i);
    }
};