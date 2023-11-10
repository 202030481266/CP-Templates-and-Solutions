// dfs 暴力穷举超时（常数太大了）
class Solution {
public:
    long long calculate(long long a, long long b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    }
    bool valid(string& s, long long target) {
        stack<long long> num;
        stack<char> op;
        for (int i = 0; i < s.size(); ++i) {
            if (isdigit(s[i])) {
                long long cur = 0, p = i;
                while (p < s.size() && isdigit(s[p])) cur = cur * 10 + s[p++] - '0';
                num.push(cur);
                i = p - 1;
            }
            else {
                if (s[i] == '+' || s[i] == '-') {
                    while (!op.empty()) {
                        long long b = num.top(); num.pop();
                        long long a = num.top(); num.pop();
                        num.push(calculate(a, b, op.top()));
                        op.pop();
                    }
                    op.push(s[i]);
                }
                else {
                    while (!op.empty() && (op.top() == '*')) {
                        long long b = num.top(); num.pop();
                        long long a = num.top(); num.pop();
                        num.push(calculate(a, b, op.top()));
                        op.pop();
                    }
                    op.push(s[i]);
                }
            }
        }
        while (!op.empty()) {
            long long b = num.top(); num.pop();
            long long a = num.top(); num.pop();
            num.push(calculate(a, b, op.top()));
            op.pop();
        }
        return num.top() == target;
    }
    vector<string> addOperators(string num, int target) {
        // dfs模拟问题，爆搜即可
        // 注意不能存在前导零
        int n = num.size();

        vector<string> ops{"-", "*", "+"};
        vector<string> ans;

        function<void(string,int)> dfs = [&](string res, int p) {
            if (p == n) {
                if (valid(res, target)) ans.push_back(res);
                return;
            }
            if (num[p] == '0') {
                if (p + 1 == n) {
                    dfs(res + to_string(0), n);
                }
                else {
                    for (string& op : ops)
                        dfs(res + to_string(0) + op, p + 1);
                }
                return;
            } // 前导零
            long long cur = 0, i = p;
            while (i < n) {
                cur = cur * 10 + num[i] - '0';
                ++i;
                if (i == n) {
                    dfs(res + to_string(cur), n);
                }
                else {
                    for (string& op : ops) {
                        dfs(res + to_string(cur) + op, i);
                    }
                }
            }
        };

        dfs("", 0);
        return ans;
    }
};


// 一种实时计算的爆搜方法，并且使用了字符数组的方法来进行保存，常数非常小
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        int n = num.length();
        vector<string> ans;

        function<void(string&, int, long, long)> backtrack = [&](string &expr, int i, long res, long mul) {
            if (i == n) {
                if (res == target) {
                    ans.emplace_back(expr);
                }
                return;
            }
            int signIndex = expr.size();
            if (i > 0) {
                expr.push_back(0); // 占位，下面填充符号
            }
            long val = 0;
            // 枚举截取的数字长度（取多少位），注意数字可以是单个 0 但不能有前导零
            for (int j = i; j < n && (j == i || num[i] != '0'); ++j) {
                val = val * 10 + num[j] - '0';
                expr.push_back(num[j]);
                if (i == 0) { // 表达式开头不能添加符号
                    backtrack(expr, j + 1, val, val);
                } else { // 枚举符号
                    expr[signIndex] = '+'; backtrack(expr, j + 1, res + val, val);
                    expr[signIndex] = '-'; backtrack(expr, j + 1, res - val, -val);
                    expr[signIndex] = '*'; backtrack(expr, j + 1, res - mul + mul * val, mul * val);
                }
            }
            expr.resize(signIndex);
        };

        string expr;
        backtrack(expr, 0, 0, 0);
        return ans;
    }
};

