// 前缀表达式
class Solution {
public:
    bool parseBoolExpr(string s) {
        int n = s.size();
        stack<char> ops;
        stack<char> num;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'f' || s[i] == 't' || s[i] == '(') {
                // & or | need to caculate
                num.push(s[i]);
            }
            else if (s[i] == '!' || s[i] == '|' || s[i] == '&') {
                ops.push(s[i]);
            }
            else if (s[i] == ')') {
                // should be always be &(e1,e2,e3) this format
                int res = (ops.top() == '|' ? 0 : 1);
                while (num.top() != '(') {
                    int x = (num.top() == 'f' ? 0 : 1);
                    if (ops.top() == '!') res = x ^ 1;
                    else if (ops.top() == '|') res |= x;
                    else res &= x;
                    num.pop();
                }
                num.pop(); // pop the (
                ops.pop(); // pop the operation
                num.push((res == 0 ? 'f' : 't'));
            }
        }
        return num.top() == 'f' ? 0 : 1;
    }
};