class Solution {
public:
    bool isNumber(string s) {
        // 只有可能出现的字母为 e / E，并且只可能出现一次
        int pos_e = -1, n = s.size();
        for (int i = 0; i < n; ++i) {
            if (isalpha(s[i])) {
                if (s[i] == 'e' || s[i] == 'E') {
                    if (pos_e != -1) return false;
                    pos_e = i;
                }
                else return false;
            }
        }

        auto check_integer = [&](string t) -> bool {
            int n = t.size(), cnt = 0;
            if (n == 0) return false;
            for (int i = 0; i < n; ++i) {
                if (t[i] == '+' || t[i] == '-') {
                    if (i > 0) return false;
                }
                else {
                    if (!isdigit(t[i])) return false;
                    ++cnt;
                }
            }
            return cnt > 0;
        };
        auto check_decimal = [&](string t) -> bool {
            int n = t.size(), p_dot = -1;
            for (int i = 0; i < n; ++i) {
                if (t[i] == '+' || t[i] == '-') {
                    if (i > 0) return false;
                }
                else if (t[i] == '.') {
                    if (p_dot != -1) return false;
                    p_dot = i;
                }
                else {
                    if (!isdigit(t[i])) return false;
                }
            }
            if (p_dot == -1) return false;
            string suf = t.substr(p_dot + 1), pre;
            if (isdigit(t[0])) pre = t.substr(0, p_dot);
            else pre = t.substr(1, p_dot - 1);
            return (suf.size() > 0) || (pre.size() > 0);
        };

        if (pos_e != -1) {
            string pre = s.substr(0, pos_e), suf = s.substr(pos_e + 1);
            return (check_decimal(pre) || check_integer(pre)) && (check_integer(suf));
        }
        return check_integer(s) || check_decimal(s);
    }
};