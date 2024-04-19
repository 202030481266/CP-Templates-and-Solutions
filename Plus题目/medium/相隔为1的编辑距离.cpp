class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int n = s.size(), m = t.size();
        if (n == m) {
            // 只能是替换
            int cnt = 1;
            for (int i = 0; i < n; ++i) {
                if (s[i] != t[i]) {
                    if (cnt) --cnt;
                    else return false;
                }
            }
            return cnt == 0;
        }
        else if (n == m + 1) {
            // 删除一个
            // 前缀
            int p = 0;
            while (p < m && s[p] == t[p]) ++p;
            if (p == 0) {
                // 只有可能是后缀
                for (int i = 1; i < n; ++i) {
                    if (s[i] != t[i - 1])
                        return false; 
                }
                return true;
            }
            ++p;
            while (p < n && s[p] == t[p - 1]) ++p;
            return p == n;
        }
        else if (n == m - 1) {
            // 添加一个
            return isOneEditDistance(t, s);
        }
        return false;
    }
};