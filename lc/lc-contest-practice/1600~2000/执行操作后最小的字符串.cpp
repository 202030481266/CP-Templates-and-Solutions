// https://leetcode.cn/problems/lexicographically-smallest-string-after-applying-operations/
// 数据量巨小，一看就是暴力
// 本题的难点在于操作的循环性质，一旦意识到操作的有限性就可以通过模拟暴力搜索到最小的字符串


class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        string anw = s;
        for(int i = 0; i <= s.size(); i++) {
            // 轮转
            s = s.substr(b, s.size()) + s.substr(0, b);
            // 修改奇数位置
            for(int j = 0; j < 10; j++) {
                for(int k = 1; k < s.size(); k += 2) {
                    s[k] += a;
                    if(s[k] > '9') {
                        s[k] = '0' + (s[k]-'9'-1);
                    }
                }
                if(b%2) {
                    // b为奇数，此时通过轮转，也能修改偶数位置
                    for(int m = 0; m < 10; m++) {
                        for(int k = 0; k < s.size(); k += 2) {
                            s[k] += a;
                            if(s[k] > '9') {
                                s[k] = '0' + (s[k]-'9'-1);
                            }
                        }   
                        anw = min(anw, s);
                    }
                } else {
                    anw = min(anw, s);
                }
            }
        }
        return anw;
    }
};

