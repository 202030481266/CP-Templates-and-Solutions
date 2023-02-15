// https://leetcode.cn/problems/regular-expression-matching/submissions/184735906/
// 字符串匹配方案数，就是经典的动态规划问题
// 使用记忆化搜索可以很方便地计算这些问题，但是细节很多，需要耐心

class Solution {
public:
    unordered_map<string, bool> memo;
    bool dp(string&s, int i, string& p, int j) {
        int m = s.size(), n = p.size();
        if (j == n) return i == m;
        if (i == m) {
            if ((n-j)%2 == 1)
                return false;
            for (; j+1 < n; j+=2) {
                if (p[j+1] != '*')
                    return false;
            }
            return true;
        }
        string key = to_string(i) + "," + to_string(j);
        if (memo.count(key)) return memo[key];
        bool res = false;
        if (s[i] == p[j] || p[j] == '.') {
            if (j < n - 1 && p[j+1] == '*') {
                res = dp(s, i, p, j+2) || dp(s, i+1, p, j);
            } else {
                res = dp(s, i+1, p, j+1);
            }
        } else {
            if (j < n - 1 && p[j+1] == '*') {
                    res = dp(s,i,p,j+2);
            } else {
                res = false;
            }
        }
        memo[key] = res;
        return res;
    }
    bool isMatch(string s, string p) {
        return dp(s,0,p,0);
    }
};